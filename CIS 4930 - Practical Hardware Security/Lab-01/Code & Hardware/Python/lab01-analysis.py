# Derek Caprio bitstream 1 responses: x, y, z
# Derek Caprio bitstream 2 responses: d, e, f
# Igli Duro bitsream 1 responses: a, b, c

import numpy as np
from scipy.spatial import distance
import statistics

#######################################################
# Igli's responses on 01 bitstream
resp_a = np.load('resp_a2.npz')
resp_b = np.load('resp_b2.npz')
resp_c = np.load('resp_c2.npz')
###
# Derek responses on 02 bitstream
resp_d = np.load('resp_d2.npz')
resp_e = np.load('resp_e2.npz')
resp_f = np.load('resp_f2.npz')
###
# Derek responses on 01 bitstream
resp_x = np.load('resp_x2.npz')
resp_y = np.load('resp_y2.npz')
resp_z = np.load('resp_z2.npz')
#########################################################


ham_dists = []
#####
#####
# Igli and Derek interchip
ax = distance.hamming(resp_a['arr_0'], resp_x['arr_0'])
ham_dists.append(ax)
ay = distance.hamming(resp_a['arr_0'], resp_y['arr_0'])
ham_dists.append(ay)
az = distance.hamming(resp_a['arr_0'], resp_z['arr_0'])
ham_dists.append(az)
bx = distance.hamming(resp_b['arr_0'], resp_x['arr_0'])
ham_dists.append(bx)
by = distance.hamming(resp_b['arr_0'], resp_y['arr_0'])
ham_dists.append(by)
bz = distance.hamming(resp_b['arr_0'], resp_z['arr_0'])
ham_dists.append(bz)
cx = distance.hamming(resp_a['arr_0'], resp_x['arr_0'])
ham_dists.append(cx)
cy = distance.hamming(resp_a['arr_0'], resp_y['arr_0'])
ham_dists.append(cy)
cz = distance.hamming(resp_a['arr_0'], resp_z['arr_0'])
ham_dists.append(cz)
print("####################################################")
print("IGLI AND DEREK INTERCHIP HAMMING DISTANCE")
print("a/x:", ax, "   a/y:", ay, "   a/z:", az)
print("b/x:", bx, "   b/y:", by, "   b/z:", bz)
print("c/x:", cx, "   c/y:", cy, "   c/z:", cz)
print("Average:", statistics.mean(ham_dists))
print("Std.Dev:", statistics.stdev(ham_dists))
ham_dists.clear()
#####
#####
# Igli intrachip
ab = distance.hamming(resp_a['arr_0'], resp_b['arr_0'])
ham_dists.append(ab)
ac = distance.hamming(resp_a['arr_0'], resp_c['arr_0'])
ham_dists.append(ac)
bc = distance.hamming(resp_b['arr_0'], resp_c['arr_0'])
ham_dists.append(bc)
print("####################################################")
print("IGLI VALID RESPONSE PAIRS HAMMING DISTANCE")
print("a/b:", ab, "   a/c:", ac, "   b/c:", bc)
print("Average:", statistics.mean(ham_dists))
print("Std.Dev:", statistics.stdev(ham_dists))
ham_dists.clear()
#####

#####
# Derek intrachip
dx = distance.hamming(resp_d['arr_0'], resp_x['arr_0'])
ham_dists.append(dx)
dy = distance.hamming(resp_d['arr_0'], resp_y['arr_0'])
ham_dists.append(dy)
dz = distance.hamming(resp_d['arr_0'], resp_z['arr_0'])
ham_dists.append(dz)
ex = distance.hamming(resp_e['arr_0'], resp_x['arr_0'])
ham_dists.append(ex)
ey = distance.hamming(resp_e['arr_0'], resp_y['arr_0'])
ham_dists.append(ey)
ez = distance.hamming(resp_e['arr_0'], resp_z['arr_0'])
ham_dists.append(ez)
fx = distance.hamming(resp_f['arr_0'], resp_x['arr_0'])
ham_dists.append(fx)
fy = distance.hamming(resp_f['arr_0'], resp_y['arr_0'])
ham_dists.append(fy)
fz = distance.hamming(resp_f['arr_0'], resp_z['arr_0'])
ham_dists.append(fz)
print("####################################################")
print("DEREK INTRACHIP HAMMING DISTANCE")
print("d/x:", dx, "   d/y:", dy, "   d/z:", dz)
print("e/x:", ex, "   e/y:", ey, "   e/z:", ez)
print("f/x:", fx, "   f/y:", fy, "   f/z:", fz)
print("Average:", statistics.mean(ham_dists))
print("Std.Dev:", statistics.stdev(ham_dists))
ham_dists.clear()
#####
#####
# Derek interchip
de = distance.hamming(resp_d['arr_0'], resp_e['arr_0'])
ham_dists.append(de)
df = distance.hamming(resp_d['arr_0'], resp_f['arr_0'])
ham_dists.append(df)
ef = distance.hamming(resp_e['arr_0'], resp_f['arr_0'])
ham_dists.append(ef)
xy = distance.hamming(resp_x['arr_0'], resp_y['arr_0'])
ham_dists.append(xy)
xz = distance.hamming(resp_x['arr_0'], resp_z['arr_0'])
ham_dists.append(xz)
yz = distance.hamming(resp_y['arr_0'], resp_z['arr_0'])
ham_dists.append(yz)
print("####################################################")
print("Derek INTERCHIP HAMMING DISTANCE")
print("d/e:", de, "   d/f:", df, "   e/f:", ef)
print("x/y:", xy, "   x/z:", xz, "   y/z:", yz)
print("Average:", statistics.mean(ham_dists))
print("Std.Dev:", statistics.stdev(ham_dists))
ham_dists.clear()
#####






















