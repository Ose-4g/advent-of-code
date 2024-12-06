s = """px{a<2006:qkq,m>2090:A,rfg}
pv{a>1716:R,A}
lnx{m>1548:A,A}
rfg{s<537:gd,x>2440:R,A}
qs{s>3448:A,lnx}
qkq{x<1416:A,crn}
crn{x>2662:A,R}
in{s<1351:px,qqz}
qqz{s>2770:qs,m<1801:hdj,R}
gd{a>3333:R,R}
hdj{m>838:A,pv}


{x=787,m=2655,a=1222,s=2876}
{x=1679,m=44,a=2067,s=496}
{x=2036,m=264,a=79,s=2244}
{x=2461,m=1339,a=466,s=291}
{x=2127,m=1623,a=2188,s=1013}"""

left, right = s.split("\n\n")

d = {}
for l in left.split("\n"):
    name, constraints = l.split("{")
    constraints = constraints[:-1]
    d[name] = []
    for cons in constraints.split(","):
        if ":" in cons:
            ll, rr = cons.split(":")
            d[name].append((ll,rr))
        else:
            d[name].append((None, cons))


def total(ins, ranges):
    ans = 0
    if ins == "R":
        return 0
    if ins == "A":
        ans = 1
        print([(r[0],r[-1]) for r in ranges])
        for a in ranges:
            ans *= len(a)
        # print(ans)
        return ans

    entry = d[ins]

    for (l, r) in entry:
        if l == None:
            return ans + total(r, ranges)
        new_ranges = [[j for j in i] for i in ranges]
        index = "xmas".index(l[0])

        # decide lambda to use
        lamb = None
        if l[1] == ">":
            lamb = lambda x: x>int(l[2:])
        else:
            lamb = lambda x: x < int(l[2:])

        # essentially split into two sets of constraints. ranges used in following iterations
        new_ranges[index] = list(filter(lamb, new_ranges[index]))
        ranges[index] = list(filter(lambda x: not lamb(x), ranges[index]))

        ans += total(r, new_ranges)
    return ans

print(total("in", [[i for i in range(1, 4001)] for j in range(4)]))
