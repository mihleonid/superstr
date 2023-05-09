import sys
import os
dir_path = os.path.dirname(os.path.realpath(__file__))
os.chdir(dir_path)
sys.path.append('../code/')

from flask import Flask, render_template, request
import random
import string
import hierarchical_graph
import datetime
import graph_drawer
import networkx as nx
import check_conjectures
from exact_solution import shortest_superstring

app = Flask(__name__, instance_relative_config=True)


def load_std_sol(folder):
    with open(folder + '/paths.txt', 'r') as paths_file:
        paths = paths_file.readlines()
        paths = [x.strip() for x in paths]
    with open(folder + '/descriptions.txt', 'r') as descs_file:
        descs = descs_file.readlines()
        descs = [x.strip() for x in descs]
        descs = [' ' if x == '' else x for x in descs]
    return list(zip(paths, descs))


def random_out_folder():
    return ''.join(random.choice(string.ascii_uppercase + string.digits) for _ in range(10))


def validate(strings):
    n = len(strings)
    if n < 2:
        return 'There must be at least 2 strings'
    # if n > 10:
    #     return 'There must be at most 10 strings'
    for x in strings:
        if not x.isalpha():
            return 'String {} contains a non-alphabetic character'.format(x)
        if len(x) < 1:
            return 'There must be no empty strings'
        if len(x) > 15:
            return 'String {} exceeds the maximum length of 15'.format(x)
        if "eps" in x:
            return 'String {} contains eps, please avoid eps as it denotes the empty string'.format(x)
    for i in range(n):
        for j in range(n):
            if (i != j) and (strings[i].find(strings[j]) >=0):
                return 'String {} is a substring of string {}'.format(strings[j], strings[i])


def empty_sol1(input_strings='', error=''):
    return render_template('index1.html', input_strings=input_strings, hier=[], exact=[], trivial=[], exact_sol='', hier_sol='', error=error)


def empty_sol(input_strings='', error=''):
    return render_template('index.html', input_strings=input_strings, hier=[], exact=[], trivial=[], exact_sol='', hier_sol='', error=error)


def get_paths_and_descriptions(drawer):
    return list(zip(drawer.paths, drawer.descriptions))


def log(input_strings, exact_sol, hier_sol):
    return "%s\nExact Solution has length %d:\n%s\nGreedy Hierarchical Solution has length %d:\n%s\n\n"\
           % (input_strings, len(exact_sol), exact_sol, len(hier_sol), hier_sol)


def log_history(input_strings, exact_sol, hier_sol):
    now = datetime.datetime.now()
    date = now.strftime("%Y-%m-%d")
    with open('static/logs/history/%s.txt' % date, 'a+') as output_file:
        output_file.write(log(input_strings, exact_sol, hier_sol))


def is_equals(g1, g2):
    e1, e2 = set(g1.edges()), set(g2.edges())
    return len(e1 ^ e2) == 0


def compute(strings):
    edges = strings[1:]
    strs = strings[0].split()
    output_folder = 'static/output/' + random_out_folder() + '/'
    drawer = graph_drawer.GraphDrawer(strs, output_folder + 'hier', False)
    hier_sol, hier_graph = hierarchical_graph.construct_greedy_solution(strs, drawer)
    hier = get_paths_and_descriptions(drawer)
    drawer.clear()

    # opt_permutation = shortest_superstring(strs)
    # opt_strings = [strs[i] for i in opt_permutation]
    # drawer.set_output_folder(output_folder + 'exact')
    # exact_sol, exact_graph = hierarchical_graph.collapse_for_permutation(opt_strings, edges, drawer)
    # exact = get_paths_and_descriptions(drawer)
    # drawer.clear()
    exact_sol, exact_graph, exact = hier_sol, hier_graph, hier

    drawer.set_output_folder(output_folder + 'trivial')
    trivial_sol, trivial_graph = hierarchical_graph.collapse_for_permutation(strs, edges, drawer, trivial=True)
    trivial = get_paths_and_descriptions(drawer)
    drawer.clear()

    check_conjectures.log_counter_examples('static/logs/counter-examples.txt', strs, exact_sol, hier_sol, hier_graph, exact_graph, trivial_graph)
    log_history(strs, exact_sol, hier_sol)

    return render_template('index.html', input_strings='\n'.join(strings), hier=hier, exact=exact, trivial=trivial, exact_sol=exact_sol, hier_sol=hier_sol,
                            is_equals_graphs = is_equals(hier_graph, trivial_graph))


@app.route('/scs', methods=['GET', 'POST'])
@app.route('/scs/index', methods=['GET', 'POST'])
def index():
    try:
        if request.method == "POST":
            if 'compute-button' in request.form:
                input = request.form['strings']
                input_strings = input.splitlines()
                return compute(input_strings)
            elif 'random-button' in request.form:
                with open('static/datasets.txt', 'r') as presets_file:
                    presets = presets_file.readlines()
                    presets = [x.strip() for x in presets]
                    num = random.randint(0, len(presets) - 1)
                    return empty_sol(presets[num].replace(' ', '\n'), '')
            elif 'reset-button' in request.form:
                return empty_sol()

        else:
            with open('static/std/input.txt', 'r') as input_file:
                input=input_file.read()
            with open('static/std/sol.txt', 'r') as sol_file:
                sol=sol_file.readlines()
                sol = [x.strip() for x in sol]
                exact_sol=sol[0]
                hier_sol=sol[1]
            hier = load_std_sol('static/std/hier')
            exact = load_std_sol('static/std/exact')
            trivial = load_std_sol('static/std/trivial')
            return render_template('index.html', input_strings=input, hier=hier, exact=exact, trivial=trivial, exact_sol=exact_sol,
                                   hier_sol=hier_sol, error='')
    except:
        with open('static/logs/exceptions.txt', 'a+') as output_file:
            output_file.write("%s\n\n%s\n\n\n" % (sys.exc_info(), request.form['strings']) )
        return empty_sol(request.form['strings'], 'There is a problem in program evaluation for this input, please report it.')




# old version
def compute1(strings):
    # input_check = validate(strings)
    input_strings = '\n'.join(strings)
    # if input_check:
    #    return empty_sol(input_strings, input_check)
    output_folder = 'static/output/' + random_out_folder() + '/'
    drawer = graph_drawer.GraphDrawer(strings,  output_folder + 'hier', False)
    hier_sol, hier_graph = hierarchical_graph.construct_greedy_solution(strings, drawer)
    hier = get_paths_and_descriptions(drawer)
    drawer.clear()
    opt_permutation = shortest_superstring(strings)
    opt_strings = [strings[i] for i in opt_permutation]
    drawer.set_output_folder(output_folder + 'exact')
    exact_sol, exact_graph = hierarchical_graph.collapse_for_permutation(opt_strings, None, drawer, drawing=True)
    exact = get_paths_and_descriptions(drawer)
    drawer.clear()
    drawer.set_output_folder(output_folder + 'trivial')
    trivial_sol, trivial_graph = hierarchical_graph.collapse_for_permutation(strings, None, drawer, drawing=True)
    trivial = get_paths_and_descriptions(drawer)
    drawer.clear()
    check_conjectures.log_counter_examples('static/logs/counter-examples.txt', input_strings, exact_sol, hier_sol, hier_graph, exact_graph, trivial_graph)
    log_history(input_strings, exact_sol, hier_sol)
    return render_template('index1.html', input_strings=input_strings, hier=hier, exact=exact, trivial=trivial, exact_sol=exact_sol, hier_sol=hier_sol)


@app.route('/scs1', methods=['GET', 'POST'])
@app.route('/scs1/index', methods=['GET', 'POST'])
def index1():
    try:
        if request.method == "POST":
            if 'compute-button' in request.form:
                input = request.form['strings']
                input_strings = input.splitlines()
                return compute1(input_strings)
            elif 'random-button' in request.form:
                with open('static/datasets.txt', 'r') as presets_file:
                    presets = presets_file.readlines()
                    presets = [x.strip() for x in presets]
                    num = random.randint(0, len(presets) - 1)
                    return empty_sol1(presets[num].replace(' ', '\n'), '')
            elif 'reset-button' in request.form:
                return empty_sol1()

        else:
            with open('static/std/input.txt', 'r') as input_file:
                input=input_file.read()
            with open('static/std/sol.txt', 'r') as sol_file:
                sol=sol_file.readlines()
                sol = [x.strip() for x in sol]
                exact_sol=sol[0]
                hier_sol=sol[1]
            hier = load_std_sol('static/std/hier')
            exact = load_std_sol('static/std/exact')
            trivial = load_std_sol('static/std/trivial')
            return render_template('index1.html', input_strings=input, hier=hier, exact=exact, trivial=trivial, exact_sol=exact_sol,
                                   hier_sol=hier_sol, error='')
    except:
        with open('static/logs/exceptions.txt', 'a+') as output_file:
            output_file.write("%s\n\n%s\n\n\n" % (sys.exc_info(), request.form['strings']) )
        return empty_sol1(request.form['strings'], 'There is a problem in program evaluation for this input, please report it.')
