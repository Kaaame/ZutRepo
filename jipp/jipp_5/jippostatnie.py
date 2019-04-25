import math as mt

a = 0
b = 0
c = 0
d = 0

deltar = 0
deltau = 0
pdeltar = 0
pdeltau = 0
x1r = 0
x2r = 0
x3r = 0
x4r = 0
x1u = 0
x2u = 0
x3u = 0
x4u = 0

sr = 0
su = 0
rr = 0
ru = 0
ir = 0 
iu = 0

irr = 0
iru = 0

p_x1r=0
p_x1u=0

o_x1r=0
o_x1u=0

def podaj_dane(a_, b_, c_, d_):
    a_ = int(input('Podaj a: '))
    b_ = int(input('Podaj b: '))
    c_ = int(input('Podaj c: '))
    d_ = int(input('Podaj d: '))

    return a_, b_, c_, d_

def formatowanie(a, b, c, d):
    if a != 0:
        print(repr(a) + 'x^2 + ',end='')
    if b != 0:
        print(repr(b) + 'x^2 + ',end='')
    if c != 0:
        print(repr(c) + ' + ',end='')
    if d != 0:
        print(repr(d) + 'i')

def oblicz_d_r(a, b, c):
    return (b*b - (4.0*a*c))

def oblicz_d_u(a, b):
    return ((-4.0)*a*d)

def oblicz_p_d_r(deltar, deltau):
    return mt.sqrt((mt.sqrt(mt.pow(deltar, 2) + mt.pow(deltau,2)) + deltar)/2)

def oblicz_p_d_u(deltar, deltau):
    return mt.sqrt((mt.sqrt(mt.pow(deltar, 2) + mt.pow(deltau,2)) - deltar)/2)

def oblicz_pierwiastki(a,b,c,d,x1r,x2r,x3r,x4r,x1u,x2u,x3u,x4u):
    if a!=0 and d==0:
        if oblicz_d_r(a,b,c) > 0:
            x1r = (-b*1.0 - oblicz_p_d_r(oblicz_d_r(a,b,c), 0))/(2*a*1.0)
            x2r = (-b*1.0 + oblicz_p_d_r(oblicz_d_r(a,b,c), 0))/(2*a*1.0)
        if (oblicz_d_r(a,b,c) == 0):
            x1r = -b/(2.0*a)
        else:
            x2r = oblicz_d_r(a,b,c)
            x2u = oblicz_p_d_r(-x2r, 0)
            x1r = (-b / (2.0*a))
            x1u = (-x2u / (2.0*a))
            x2r = x1r
            x2u = -x1u
        return x1r, x1u, x2r, x2u, x3r, x3u, x4r, x4u
    if a==0 and b != 0 and d == 0:
        x1r = (-c)/(b*1.0)
        return x1r, x1u, x2r, x2u, x3r, x3u, x4r, x4u
    if a == 0 and b != 0 and d !=0:
        x1r = (-c)/(b*1.0)
        x1u = (-d)/(b*1.0)
        return x1r, x1u, x2r, x2u, x3r, x3u, x4r, x4u
    else:
        x3r = oblicz_d_r(a,b,c)
        x4r = oblicz_d_u(a,d)
        x1r = (-b*1.0 - oblicz_p_d_r(x3r,x4r))/(2.0*a)
        x2r = (-b*1.0 + oblicz_p_d_r(x3r,x4r))/(2.0*a)
        x1u = (oblicz_p_d_u(x3r, x4r))/(2.0*a)
        x2u = -(oblicz_p_d_u(x3r, x4r))/(2.0*a)
        x3r = -x1r
        x4r = -x2r
        x3u = x2u
        x4u = x1u
    return x1r, x1u, x2r, x2u, x3r, x3u, x4r, x4u

def dodaj(x1r, x2r, x3r, x4r, x1u,
	x2u, x3u, x4u, sr, su):
    sr = x1r + x2r + x3r + x4r
    su = x1u + x2u + x3u + x4u
    return sr, su

def odejmij(x1r, x2r, x3r, x4r, x1u,
	x2u, x3u, x4u, rr, ru):
    rr = x1r - x2r - x3r - x4r
    ru = x1u - x2u - x3u - x4u
    return rr, ru

def pomnoz(x1r, x2r, x3r, x4r, x1u,
	x2u, x3u, x4u, ir, iu):
    ir = x1r + x2r + x3r + x4r
    iu = x1u + x2u + x3u + x4u
    return ir, iu

def iloraz(a,b,c,d,x1r,x2r,x3r,x4r,x1u,x2u,x3u,x4u,irr,iru):
    if a != 0 and d == 0 and oblicz_d_r(a,b,c) > 0.0:
        if x2r != 0:
            irr = x1r/x2r
        else:
            irr = 0
        return irr, iru
    if a != 0 and d == 0 and oblicz_d_r(a,b,c) < 0:
        irr = (x1r*x2r + x1u*x2u)/(mt.pow(x2r,2) + mt.pow(x2u, 2))
        iru = (x1r*x2r - x1u*x2u)/(mt.pow(x2r,2) + mt.pow(x2u, 2))
        return irr, iru
    if a!=0 and d!=0:
        x1 = complex(x1r, x1u)
        x2 = complex(x2r, x2u)
        x3 = complex(x3r, x3u)
        x4 = complex(x4r, x4u)
        res = x1/x2/x3/x4
        return res, iru
    return irr, iru

def przeciwny(a,b,c,d,x1r,x2r,x3r,x4r,x1u,x2u,x3u,x4u, p_x1r, p_x1u):
    if (a!=0 and d==0 and oblicz_d_r(a,b,c) == 0):
        p_x1r = -x1r
    if (a==0 and b!=0 and d==0):
        p_x1r = -x1r
    if a==0 and b != 0 and d!=0:
        p_x1r = -x1r
        p_x1u = -x1u
    return p_x1r, p_x1u

def odwrotny(a,b,c,d,x1r,x2r,x3r,x4r,x1u,x2u,x3u,x4u,o_x1r,o_x1u):
    if (a!=0 and d==0 and oblicz_d_r(a,b,c) == 0):
        o_x1r = 1/x1r
    if a==0 and b != 0 and d!=0:
        o_x1r = x1r/(mt.pow(x1r,2)+mt.pow(x1u,2))
        o_x1u = -x1u/(mt.pow(x1r,2)+mt.pow(x1u,2))        
    return o_x1r, o_x1u
        

def wyswietlenie(a,b,c,d,x1r,x2r,x3r,x4r,x1u,x2u,x3u,x4u,sr,su,rr,ru,ir,iu,irr,iru,p_x1r,p_x1u,o_x1r,o_x1u):
    if a!=0 and d==0:
        if oblicz_d_r(a,b,c) > 0:
            print('x1 = ' + repr(x1r) + '\nx2 = ' + repr(x2r))
        if (oblicz_d_r(a,b,c) == 0):
            print('x1 = ' + repr(x1r) + '\n')
        else:
            print('x1 = ' + repr(x1r) + '+(' + repr(x1u)+ ')i' + '\nx2 = ' + repr(x2r) + '+(' + repr(x2u)+ ')i')
    if a==0 and b != 0 and d == 0:
        print('x1 = ' + repr(x1r) + '+(' + repr(x1u)+ ')i')
    if a == 0 and b != 0 and d !=0:
        print('x1 = ' + repr(x1r) + '+(' + repr(x1u)+ ')i')
    if a==0 and b==0 and (d!=0 or c!=0):
        print('Rownianie sprzeczne')
    if a==0 and b==0 and c==0 and d==0:
        print('Rownianie tozsame')
    else:
        print('x1 = ' + repr(x1r) + '+(' + repr(x1u)+ ')i' + '\nx2 = ' + repr(x2r) + '+(' + repr(x2u)+ ')i')
        print('x3 = ' + repr(x3r) + '+(' + repr(x3u)+ ')i' + '\nx4 = ' + repr(x4r) + '+(' + repr(x4u)+ ')i')
    print('dodaj = ' + repr(sr) + ' + ' +repr(su) +'i')
    print('odejmij = ' + repr(rr) + ' + ' +repr(ru) +'i')
    print('roznica = ' + repr(ir) + ' + ' +repr(iu) +'i')

    print('iloraz = ' + repr(irr) + ' + ' +repr(iru) +'i')
    print('przeciwne = ' + repr(p_x1r) + ' + ' +repr(p_x1u) +'i')
    print('odwrotne = ' + repr(o_x1r) + ' + ' +repr(o_x1u) +'i')
    return

res = podaj_dane(a, b, c, d)

a = int(res[0])
b = int(res[1])
c = int(res[2])
d = int(res[3])

formatowanie(a,b,c,d)
res = oblicz_pierwiastki(a,b,c,d,x1r,x2r,x3r,x4r,x1u, x2u, x3u, x4u)

x1r = res[0]
x1u = res[1]

x2r = res[2]
x2u = res[3]

x3r = res[4]
x3u = res[5]

x4r = res[6]
x4u = res[7]

res = dodaj(x1r,x2r,x3r,x4r,x1u,x2u,x3u,x4u,sr,su)
sr = res[0]
su = res[1]

res = odejmij(x1r,x2r,x3r,x4r,x1u,x2u,x3u,x4u,rr,ru)
rr = res[0]
ru = res[1]

res = pomnoz(x1r,x2r,x3r,x4r,x1u,x2u,x3u,x4u,ir,iu)
ir = res[0]
iu = res[1]

res = iloraz(a,b,c,d,x1r,x2r,x3r,x4r,x1u,x2u,x3u,x4u,irr,iru)
irr = res[0]
iru = res[1]

res = przeciwny(a,b,c,d,x1r,x2r,x3r,x4r,x1u,x2u,x3u,x4u,p_x1r,p_x1u)
p_x1r = res[0]
p_x1u = res[1]

res = odwrotny(a,b,c,d,x1r,x2r,x3r,x4r,x1u,x2u,x3u,x4u,o_x1r,o_x1u)
o_x1r = res[0]
o_x1u = res[1]

wyswietlenie(a,b,c,d,x1r,x2r,x3r,x4r,x1u,x2u,x3u,x4u,sr,su,rr,ru,ir,iu,irr,iru,p_x1r,p_x1u,o_x1r,o_x1u)
