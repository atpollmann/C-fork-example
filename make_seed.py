#!/usr/bin/python
'Author: Rene Tapia Pincheira rene.tapia@usach.cl'
import random;
import string;

tipoFondo = ['A', 'B', 'C', 'D', 'E'];
tipoActivo = ['RV', 'RF'];

type1 = [
    'ACC',
    'ACE',
    'AEE',
    'CFID',
    'CFMV',
    'CFMD',
    'CMED',
    'CMEV',
    'ETFA',
    'ETFB',
    'ETFC'
];
type2 = [
    'DPF',
    'ECO'
]

def makeString(n = 10):
    return ''.join(random.choice(string.ascii_uppercase + string.digits) for _ in range(n))

for i in xrange(0,5000):
    L = [
        random.choice(tipoFondo),
        makeString(20),
        random.choice(type1 + type2),
        str(random.randint(1,2)),
        str(int(random.random()*100) / 100.0),
        str(random.randint(1,346)*386),
        str(int(random.random()*120))
    ];
    print ';'.join(L) + '\n',;
