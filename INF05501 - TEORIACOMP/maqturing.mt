1,#
X,Y,S,$,!
@
B
q0,q1,q2,q2!,q!,qx1,qx2,qx3,q3,q4,q5,q6,q6$,q$,qy1,qy2,q7,qi,qc,q8,q9,q10,q11,q12,q12a,q13,qr,qf
q0
qf
X -> digito 'consumido' pra ser substituido depois de multiplicar, 1o numero
Y -> digito 'consumido' pra ser substituido depois de multiplicar, 2o numero
S -> digito 'consumido' na subtracao
! -> sepador de entrada/numeros sendo multiplicados
$ -> separador dos dois numeros já multiplicados
B -> branco

q0: encontra e consome 1o digito do 1o numero
q1: encontra 2o numero, andando ate #

q8: comeca subtracao

posso mudar a posicao inicial da fita? se sim, qi mudaria @ por B e qc mudaria $ por @

[q9,!] Escreva: estado, símbolo, movimento