import networkx as nx
import graph_drawer
import string_methods

__empty_node_name__ = "eps"

def get_upper_indegree(graph, v):
    assert v != "" and v != __empty_node_name__
    if not graph.has_node(v):
        return 0

    upper_indegree = 0
    for u in graph.predecessors(v):
        if len(u) == len(v) + 1:
            upper_indegree += graph.number_of_edges(u, v)
    return upper_indegree


def get_upper_outdegree(graph, v):
    assert v != "" and v != __empty_node_name__
    if not graph.has_node(v):
        return 0

    upper_outdegree = 0
    for u in graph.successors(v):
        if len(u) == len(v) + 1:
            upper_outdegree += graph.number_of_edges(v, u)
    return upper_outdegree


def get_lower_indegree(graph, v):
    assert v != "" and v != __empty_node_name__
    if not graph.has_node(v):
        return 0

    lower_indegree = 0
    for u in graph.predecessors(v):
        if len(u) == len(v) - 1 or (len(v) == 1 and u == __empty_node_name__):
            lower_indegree += graph.number_of_edges(u, v)
    return lower_indegree


def get_lower_outdegree(graph, v):
    assert v != "" and v != __empty_node_name__
    if not graph.has_node(v):
        return 0

    lower_outdegree = 0
    for u in graph.successors(v):
        if len(u) == len(v) - 1 or (len(v) == 1 and u == __empty_node_name__):
            lower_outdegree += graph.number_of_edges(v, u)
    return lower_outdegree


def set_of_edges_to_superstring(graph):
    print('@ 1')
    cycle = list(nx.eulerian_circuit(graph, 'eps'))
    print(cycle)
    print('@ 2')
    superstring = ''
    print('@ 3')
    for cur, next in cycle:
        print('@ 4')
        if next != 'eps' and (cur == 'eps' or len(next) > len(cur)):
            print('@ 5')
            superstring += next[-1]
    print('@ 6')
    return superstring


def get_graph(edges):
    greedy_graph = nx.MultiDiGraph()
    for edge in edges:
        e = edge.split()
        if e[0] == '-':
            e[0] = __empty_node_name__
        if e[1] == '-':
            e[1] = __empty_node_name__
        greedy_graph.add_edge(e[0], e[1])
    return greedy_graph


def construct_greedy_solution_vz(strings, edges, drawer):
    greedy_graph = get_graph(edges)
    drawer.draw(greedy_graph, drawing=True)
    return 'greedy_superstring', greedy_graph


def construct_greedy_solution(strings, drawer):
    greedy_graph = nx.MultiDiGraph()
    processed_nodes = []

    drawer.draw(greedy_graph, processed_nodes, "initial hierarchical graph")
    drawer.draw(greedy_graph, processed_nodes, "we first process input strings")

    for s in sorted(strings):
        pref = s[:-1] if s[:-1] != "" else "eps"
        suff = s[1:]  if s[1:]  != "" else "eps"

        processed_nodes.append(s)
        drawer.draw(greedy_graph, processed_nodes,
            "{} is an input string hence we add two bottom edges to it: {}->{}->{}".format(s, pref, s, suff))

        greedy_graph.add_edge(pref, s)
        greedy_graph.add_edge(s, suff)

        drawer.draw(greedy_graph, processed_nodes)

    drawer.draw(greedy_graph, processed_nodes, "we now process nodes from top to bottom in lexicographical ordering")

    max_level = max(len(s) for s in strings)
    cur_level = max_level - 1

    while cur_level:
        cur_level_vertices = sorted([v for v in drawer.HG.nodes() if len(v) == cur_level])
        cur_level -= 1

        for v in cur_level_vertices:
            if v == __empty_node_name__:
                continue

            processed_nodes.append(v)
            drawer.draw(greedy_graph, processed_nodes, "consider node {}".format(v))

            if not greedy_graph.has_node(v):
                continue

            upper_indegree = get_upper_indegree(greedy_graph, v)
            upper_outdegree = get_upper_outdegree(greedy_graph, v)

            if upper_indegree > upper_outdegree:
                suff = v[1:] if v[1:] != "" else "eps"
                for _ in range(upper_indegree - upper_outdegree):
                    drawer.draw(greedy_graph, processed_nodes, "to balance {}, add edge {}->{}".format(v, v, suff))
                    greedy_graph.add_edge(v, suff)
                    drawer.draw(greedy_graph, processed_nodes)
                assert greedy_graph.in_degree(v) == greedy_graph.out_degree(v)
            elif upper_indegree < upper_outdegree:
                pref = v[:-1] if v[:-1] != "" else "eps"
                for _ in range(upper_outdegree - upper_indegree):
                    drawer.draw(greedy_graph, processed_nodes,
                                               "to balance {}, add edge {}->{}".format(v, pref, v))
                    greedy_graph.add_edge(pref, v)
                    drawer.draw(greedy_graph, processed_nodes)
                assert greedy_graph.in_degree(v) == greedy_graph.out_degree(v)
            else:
                assert upper_indegree == upper_outdegree

                # check whether we need to connect it to the rest of the graph
                sccs = nx.strongly_connected_components(greedy_graph)
                sccs = [C for C in sccs if v in C]
                assert len(sccs) == 1

                wccs = nx.weakly_connected_components(greedy_graph)
                wccs = [C for C in wccs if v in C]
                assert len(wccs) == 1

                scc = sccs[0]
                wcc = wccs[0]

                scc = sorted(scc)
                wcc = sorted(wcc)

                min_length_string_in_wcc = min(len(z) for z in wcc)

                #if not greedy_graph.has_node("eps") and scc == wcc and len(v) == min_length_string_in_wcc and sorted([u for u in scc if len(u) == len(v)])[-1] == v:
                if not "eps" in scc and scc == wcc and len(v) == min_length_string_in_wcc and sorted([u for u in scc if len(u) == len(v)])[-1] == v:
                    suff = v[1:] if v[1:] != "" else "eps"
                    pref = v[:-1] if v[:-1] != "" else "eps"

                    drawer.draw(greedy_graph, processed_nodes, "adding edges {}->{}->{} to connect the component to eps".format(pref, v, suff))

                    greedy_graph.add_edge(v, suff)
                    greedy_graph.add_edge(pref, v)
                    assert greedy_graph.in_degree(v) == greedy_graph.out_degree(v)

                    drawer.draw(greedy_graph, processed_nodes)
                else:
                    drawer.draw(greedy_graph, processed_nodes, "{} is balanced, skip it".format(v))

    drawer.draw(greedy_graph, processed_nodes, "Done!")
    greedy_superstring = set_of_edges_to_superstring(greedy_graph)
    drawer.draw(greedy_graph, processed_nodes, "this is the greedy hierarchical solution: " + greedy_superstring, drawing=True)
    return greedy_superstring, greedy_graph


def permutation_to_solution(strings):
    solution_graph = nx.MultiDiGraph()

    s = strings[0]
    for i in range(len(s)):
        pref = s[:i] if s[:i] != "" else __empty_node_name__
        next_pref = s[:i + 1]
        solution_graph.add_edge(pref, next_pref)

    for i in range(0, len(strings) - 1):
        s = strings[i]
        next_s = strings[i + 1]
        overlap = next_s[:string_methods.overlap(s, next_s)]

        for j in range(len(s) - len(overlap)):
            suff = s[j:]
            next_suf = s[j + 1:] if s[j + 1:] != "" else __empty_node_name__
            solution_graph.add_edge(suff, next_suf)

        for j in range(len(overlap), len(next_s)):
            pref = next_s[:j] if next_s[:j] != "" else __empty_node_name__
            next_pref = next_s[:j + 1]
            solution_graph.add_edge(pref, next_pref)

    s = strings[-1]
    for i in range(len(s)):
        suff = s[i:]
        next_suff = s[i + 1:] if s[i + 1:] != "" else __empty_node_name__
        solution_graph.add_edge(suff, next_suff)

    return solution_graph


def double_and_collapse(strings, drawer, solution_graph, drawing=False):
    # assert nx.is_eulerian(solution_graph)
    assert solution_graph.has_node(__empty_node_name__)
    assert all(solution_graph.has_node(s) for s in strings)

    processed_nodes = []

    drawer.draw(nx.MultiDiGraph(), processed_nodes, "initial hierarchical graph")
    drawer.draw(solution_graph, processed_nodes, "this is the initial solution: {}".format(set_of_edges_to_superstring(solution_graph)))

    drawer.draw(solution_graph, processed_nodes, "we now double every edge of the initial solution")
    edges = list(solution_graph.edges())
    for (u, v) in edges:
        solution_graph.add_edge(u, v)
    drawer.draw(solution_graph, processed_nodes)

    drawer.draw(solution_graph, processed_nodes, "we now start collapsing")

    nodes = list(drawer.HG.nodes())
    nodes.remove(__empty_node_name__)
    nodes.sort(key=lambda z: (-len(z), z))

    for v in nodes:
        # if len(processed_nodes) > 0 and len(v) == len(processed_nodes[-1]) - 1:
        #     check_property_after_collapsing_level(solution_graph, processed_nodes, drawer)

        processed_nodes.append(v)
        drawer.draw(solution_graph, processed_nodes, "process {}".format(v))

        one_more_try = True
        while one_more_try:
            assert nx.is_strongly_connected(solution_graph)
            one_more_try = False

            if get_lower_indegree(solution_graph, v) == 0 or get_lower_outdegree(solution_graph, v) == 0:
                drawer.draw(solution_graph, processed_nodes, "there are no lower edges, skip this node")
                continue

            if v in strings and get_lower_indegree(solution_graph, v) == 1 and get_lower_outdegree(solution_graph, v) == 1:
                drawer.draw(solution_graph, processed_nodes, "{} is an input node so we cannot collapse its pair of edges".format(v))
                continue

            for pref in solution_graph.predecessors(v):
                for suf in solution_graph.successors(v):
                    if one_more_try:
                        break

                    if len(v) > 1 and (len(pref) != len(v) - 1 or len(suf) != len(v) - 1 or one_more_try):
                        continue

                    if len(v) == 1 and (pref != __empty_node_name__ or suf != __empty_node_name__):
                        continue

                    # try collapsing this pair
                    mirror = solution_graph.copy()
                    mirror.remove_edge(pref, v)
                    mirror.remove_edge(v, suf)

                    if len(v) > 1:
                        bottomv = v[1:len(v) - 1]
                        if bottomv == "":
                            bottomv = __empty_node_name__
                        mirror.add_edge(pref, bottomv)
                        mirror.add_edge(bottomv, suf)

                    # clean the graph (so that it does not contain isolated nodes)
                    # TODO: inefficient
                    remove_one_more_node = True
                    while remove_one_more_node:
                        remove_one_more_node = False
                        for mv in mirror.nodes():
                            if mv != __empty_node_name__ and mirror.in_degree(mv) == 0:
                                assert mirror.out_degree(mv) == 0
                                mirror.remove_node(mv)
                                remove_one_more_node = True
                                break

                    if not nx.is_weakly_connected(mirror):
                        drawer.draw(solution_graph, processed_nodes,
                            "the pair of edges {}->{}->{} cannot be mirrored as it would break connectivity".format(
                                pref, v, suf
                            ), drawing=drawing)

                        sccs = nx.strongly_connected_components(mirror)
                        sccs = [C for C in sccs if v in C]
                        scc = sccs[0]
                        assert __empty_node_name__ not in scc
                    else:
                        one_more_try = True
                        assert nx.is_eulerian(mirror)
                        drawer.draw(solution_graph,
                                    highlighted_nodes=processed_nodes,
                                    description="we will now collapse the edges {}->{}->{}".format(pref, v, suf),
                                    highlighted_edges=[(pref, v), (v, suf)]
                                    )
                        solution_graph = mirror
                        drawer.draw(solution_graph, processed_nodes)

                        # check some property after a successful collapse
                        #print("we have just collapsed", v)
                        #check_property_after_collapsing_pair_of_edges(solution_graph, processed_nodes, drawer)
    drawer.draw(solution_graph, processed_nodes, "Done!", drawing=True)
    return solution_graph


def check_property_after_collapsing_pair_of_edges(solution_graph, processed_nodes, drawer):
    test_graph = solution_graph.copy()
    test_graph.remove_nodes_from(processed_nodes)
    assert nx.is_weakly_connected(test_graph)

    # for z in test_graph.nodes():
    #     if z == __empty_node_name__:
    #         continue
    #
    #     last_processed_node = processed_nodes[-1]
    #     if len(z) != len(last_processed_node):
    #         continue
    #
    #     indeg = get_upper_indegree(test_graph, z)
    #     outdeg = get_upper_outdegree(test_graph, z)
    #
    #     if indeg == 0 and outdeg == 0:
    #         continue
    #
    #     if indeg > outdeg:
    #         assert nx.has_path(test_graph, z, __empty_node_name__)
    #     elif indeg < outdeg:
    #         assert nx.has_path(test_graph, __empty_node_name__, z)
    #     else:
    #         print("Argh", z)
    #         assert nx.has_path(test_graph, z, __empty_node_name__)
    #         assert nx.has_path(test_graph, __empty_node_name__, z)


# def check_property_after_collapsing_level(solution_graph, processed_nodes, drawer):
#     test_graph = solution_graph.copy()
#     test_graph.remove_nodes_from(processed_nodes)
#
#     for c in nx.weakly_connected_components(test_graph):
#         if nx.is_eulerian(test_graph.subgraph(c).copy()):
#             print("eulerian")



def collapse_for_permutation(strings, edges, drawer, trivial=False, drawing=False):
    if trivial:
        solution_graph = get_graph(edges)
    else:
        solution_graph = permutation_to_solution(strings)
    superstring = set_of_edges_to_superstring(solution_graph)
    final_graph = double_and_collapse(strings, drawer, solution_graph, drawing=drawing)
    return superstring, final_graph

if __name__ == '__main__':
    #strings = ["dabababab", "babababad", "abababababab", "babababababa"]
    #strings = ["abc", "bca", "cab"]
    #strings = ["abcd", "bcde", "cdeb", "debc", "ebcd", "bcda", "cdab", "dabc"]
    #strings = ["ababba", "abbaaa", "baaaab", "aaabab", "ababab", "cdcddc", "cddccc", "dccccd", "cccdcd", "cdcdcd"]
    strings = ["ab", "ba"]
    drawer = graph_drawer.GraphDrawer(strings, output_dir="output", print_description=True, disable=False)
    collapse_for_permutation(strings, drawer)