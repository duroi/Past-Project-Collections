import matplotlib.pyplot as plt
import numpy as np

#x = list(range(0, 17))
x = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16']
#y =list(range(0, 5001))
y_vals = [0] * 17


# load responses
# Igli's responses on 01 bitstream
resp_a = np.load("resp_a2.npz")
resp_b = np.load("resp_b2.npz")
resp_c = np.load("resp_c2.npz")
###
# Derek's responses on 02 bitstream
resp_d = np.load("resp_d2.npz")
resp_e = np.load("resp_e2.npz")
resp_f = np.load("resp_f2.npz")
###
# Derek's responses on 01 bitstream
resp_x = np.load("resp_x2.npz")
resp_y = np.load("resp_y2.npz")
resp_z = np.load("resp_z2.npz")


# count number of bits different in each response
##############################################################
#a/x comparison -- partner to partner interchip
print("generating first graph...")
for i in range(len(resp_d['arr_0'])):
	num_different = 0
	for j in range(16):
		#print("first looping i,j:", i, j)
		if resp_a['arr_0'][j] != resp_x['arr_0'][j]:
			#y_vals[j] = y_vals[j] + 1
			num_different = num_different + 1
	y_vals[num_different] = y_vals[num_different] + 1
# plot
plt.bar(x, y_vals, color='green')
plt.xlabel("# of bits different")
plt.ylabel("# of occurences")
plt.title("Partner to Partner Interchip Comparison")
plt.savefig("partner_to_partner_interchip.png")

###
#e/x comparison -- intrachip
print("generating second graph...")
y_vals = [0] * 17
for i in range(len(resp_d['arr_0'])):
	num_different = 0
	for j in range(16):
		#print("second looping i,j:", i, j)
		if resp_e['arr_0'][j] != resp_x['arr_0'][j]:
			#y_vals[j] = y_vals[j] + 1
			num_different = num_different + 1
	y_vals[num_different] = y_vals[num_different] + 1
# plot
plt.bar(x, y_vals, color='green')
plt.xlabel("# of bits different")
plt.ylabel("# of occurences")
plt.title("Intrachip Comparison")
plt.savefig("intrachip.png")

###
#d/e comparison -- valid interchip CRPs
print("generating third graph...")
y_vals = [0] * 17
for i in range(len(resp_a['arr_0'])):
	num_different = 0
	for j in range(16):
		#print("third looping i,j:", i, j)
		if resp_a['arr_0'][j] != resp_b['arr_0'][j]:
			#y_vals[j] = y_vals[j] + 1
			num_different = num_different + 1
	y_vals[num_different] = y_vals[num_different] + 1
# plot
plt.bar(x, y_vals, color='green')
plt.xlabel("# of bits different")
plt.ylabel("# of occurences")
plt.title("Valid CRP Comparisons")
plt.savefig("valid_crps.png")



