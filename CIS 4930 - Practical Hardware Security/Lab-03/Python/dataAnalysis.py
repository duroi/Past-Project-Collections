from NIST import TRNGtester
import matplotlib.pyplot as plt


###################################################################################
"""""
RO_1M_test = TRNGtester('C:\\Users\\duroi\\Documents\\Lab-03\\Python\\RO_1M.bin',)

RO_1M_pval = RO_1M_test.run_nist_tests()


min = RO_1M_pval[10][0]
for i in RO_1M_pval[10]:
    if min > i:
        min = i

RO_1M_pval[10] = min

min = RO_1M_pval[13][0]
for i in RO_1M_pval[13]:
    if min > i:
        min = i

RO_1M_pval[13] = min

min = RO_1M_pval[14][0]
for i in RO_1M_pval[14]:
    if min > i:
        min = i

RO_1M_pval[14] = min

print(RO_1M_pval)

test = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]

fig = plt.figure(figsize = (20, 10))
 
# creating the bar plot
plt.bar(test, RO_1M_pval, color ='forestgreen',
        width = 0.4)
 
plt.xlabel("NIST Test")
plt.ylabel("p-value")
plt.title("NIST p-values for RO 1 Million Bits")
plt.savefig('RO_1M.png')

"""
####################################################################################

""""

RO_10M_test = TRNGtester('C:\\Users\\duroi\\Documents\\Lab-03\\Python\\RO_10M.bin',)

RO_10M_pval = RO_10M_test.run_nist_tests()

print(RO_10M_pval)

min = RO_10M_pval[10][0]
for i in RO_10M_pval[10]:
    if min > i:
        min = i

RO_10M_pval[10] = min

min = RO_10M_pval[13][0]
for i in RO_10M_pval[13]:
    if min > i:
        min = i

RO_10M_pval[13] = min

min = RO_10M_pval[14][0]
for i in RO_10M_pval[14]:
    if min > i:
        min = i

RO_10M_pval[14] = min

print(RO_10M_pval)

test = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]

fig = plt.figure(figsize = (20, 10))
 
# creating the bar plot
plt.bar(test, RO_10M_pval, color ='forestgreen',
        width = 0.4)
 
plt.xlabel("NIST Test")
plt.ylabel("p-value")
plt.title("NIST p-values for RO 10 Million Bits")
plt.savefig('RO_10M.png')

"""
####################################################################################

"""
GARO_1M_test= TRNGtester('C:\\Users\\duroi\\Documents\\Lab-03\\Python\\GARO_1M.bin')

GARO_1M_pval = GARO_1M_test.run_nist_tests()

min = GARO_1M_pval[10][0]
for i in GARO_1M_pval[10]:
    if min > i:
        min = i

GARO_1M_pval[10] = min

min = GARO_1M_pval[13][0]
for i in GARO_1M_pval[13]:
    if min > i:
        min = i

GARO_1M_pval[13] = min

min = GARO_1M_pval[14][0]
for i in GARO_1M_pval[14]:
    if min > i:
        min = i

GARO_1M_pval[14] = min

print(GARO_1M_pval)

test = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]

fig = plt.figure(figsize = (20, 10))
 
# creating the bar plot
plt.bar(test, GARO_1M_pval, color ='forestgreen',
        width = 0.4)
 
plt.xlabel("NIST Test")
plt.ylabel("p-value")
plt.title("NIST p-values for GARO 1 Million Bits")
plt.savefig('GARO_1M.png')

"""
########################################################################################

GARO_10M_test = TRNGtester('C:\\Users\\duroi\\Documents\\Lab-03\\Python\\GARO_10M.bin')

GARO_10M_pval = GARO_10M_test.run_nist_tests()

min = GARO_10M_pval[10][0]
for i in GARO_10M_pval[10]:
    if min > i:
        min = i

GARO_10M_pval[10] = min

min = GARO_10M_pval[13][0]
for i in GARO_10M_pval[13]:
    if min > i:
        min = i

GARO_10M_pval[13] = min

min = GARO_10M_pval[14][0]
for i in GARO_10M_pval[14]:
    if min > i:
        min = i

GARO_10M_pval[14] = min

print(GARO_10M_pval)

test = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]

fig = plt.figure(figsize = (20, 10))
 
# creating the bar plot
plt.bar(test, GARO_10M_pval, color ='forestgreen',
        width = 0.4)
 
plt.xlabel("NIST Test")
plt.ylabel("p-value")
plt.title("NIST p-values for GARO 10 Million Bits")
plt.savefig('GARO_10M.png')





