#!/usr/bin/env python
import matplotlib.pyplot as plt
import numpy as np
import random
import math
area = [
        [0, 0, 1, 3, 1],
        [0, 1, 1, -2, -1]
]
edge = 1.0
areax, areay = area[0], area[1]
minx, maxx = min(areax), max(areax)
miny, maxy = min(areay), max(areay)
def inArea(p):
    inarea = False
    px, py = p[0], p[1]
    for i in range(len(areax)):
        i1, i2 = i, (i + 1) % len(areax)
        p1 = [areax[i1] - px, areay[i1] - py]
        p1x, p1y = p1[0], p1[1]
        p2 = [areax[i2] - px, areay[i2] - py]
        p2x, p2y = p2[0], p2[1]
        if (p1y*p2y < 0) and ((p2x*p1y - p1x*p2y)/(p1y - p2y) < 0):
            inarea = not inarea
    return inarea
def randp():
    p = [minx - 1, miny - 1]
    while not inArea(p):
        p = [random.uniform(minx, maxx), random.uniform(miny, maxy)]
    return p
total = 10**4
tmp = 0
for i in range(total):
    p = [random.uniform(minx, maxx), random.uniform(miny, maxy)]
    if inArea(p):
        tmp += 1
area = 1.0 * (maxx - minx) * (maxy - miny) * tmp / total
print area
number = int(3*math.floor(area / (3**0.5 / 4 * edge**2)))
distance = (area/number/np.pi)**0.5
print distance

plt.plot(areax, areay, 'r')
plt.plot([areax[-1], areax[0]], [areay[-1], areay[0]], 'r')
plt.axis([minx-1, maxx+1, miny-1, maxy+1])
setp = []
for i in range(number):
    setp.append(randp())
#print setp
#while True:
for n in range(100):
    maxnorm = 0
    for i in range(len(setp)):
        pi = setp[i]
        pif = np.array([0, 0])
        pix, piy = pi[0], pi[1]
        for j in range(len(setp)):
            if i != j:
                pj = setp[j]
                pjx, pjy = pj[0], pj[1]
                f = np.array([pix - pjx, piy - pjy])
                norm = np.linalg.norm(f)
                if norm < edge:
                    pif = pif + f / (norm / distance)**3
        while True:
            pn = [setp[i][0] + pif[0], setp[i][1]]
            if (inArea(pn)):
                setp[i] = pn
                break
            pif[0] *= 0.1
        while True:
            pn = [setp[i][0], setp[i][1] + pif[1]]
            if (inArea(pn)):
                setp[i] = pn
                break
            pif[1] *= 0.1
        maxnorm = max([maxnorm, np.linalg.norm(pif)])
    if (maxnorm < 0):#distance*0):
        break
    #print maxnorm
#print setp
for i in range(len(setp)):
    p1 = setp[i]
    plt.plot(p1[0], p1[1], '*')
    print i, p1
    '''
    min1 = -1
    for j in range(len(setp)):
        p2 = setp[j]
        if i != j:
            if min1 == -1:
                min1 = j
            elif np.linalg.norm(np.array([p1[0] - p2[0], p1[1] - p2[1]])) < np.linalg.norm(np.array([p1[0] - setp[min1][0], p1[1] - setp[min1][1]])):
                min1 = j
    print i, min1
    plt.plot([p1[0], setp[min1][0]], [p1[1], setp[min1][1]], 'b')
    min2 = -1
    for j in range(len(setp)):
        p2 = setp[j]
        if i != j and j != min1:
            if min2 == -1:
                min2 = j
            elif np.linalg.norm(np.array([p1[0] - p2[0], p1[1] - p2[1]])) < np.linalg.norm(np.array([p1[0] - setp[min2][0], p1[1] - setp[min2][1]])):
                min2 = j
    print i, min2
    plt.plot([p1[0], setp[min2][0]], [p1[1], setp[min2][1]], 'b')
    min3 = -1
    for j in range(len(setp)):
        p2 = setp[j]
        if i != j and j != min1 and j != min2:
            if min3 == -1:
                min3 = j
            elif np.linalg.norm(np.array([p1[0] - p2[0], p1[1] - p2[1]])) < np.linalg.norm(np.array([p1[0] - setp[min3][0], p1[1] - setp[min3][1]])):
                min3 = j
    print i, min3
    plt.plot([p1[0], setp[min3][0]], [p1[1], setp[min3][1]], 'b')
    '''
for i in range(len(setp)):
    p1 = setp[i]
    dis = []
    for j in range(i):
        p2 = setp[j]
        dis.append(np.linalg.norm([p1[0] - p2[0], p1[1] - p2[1]]))
    if dis:
        print i, min(dis)
plt.show()
