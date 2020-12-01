1,#
X,Y,S,$,!
@
B
q0,q1,q2,q2!,q!,qx1,qx2,qx3,q3,q4,q5,q6,q6$,q$,qy1,qy2,q7,qi,qc,q8,q9,q10,q11,q12,q12a,q13,qr,qi1,qc1,qf
q0
qf
q!,1,,q!,1,D,,,q!,B,,qx1,!,D,,,q$,1,,q$,1,D,,,q$,B,,qy1,$,D,,,q0,#,,q1,#,E,,,q0,1,,q0,1,D,,,q0,@,,q0,@,D,,,q1,#,,qf,B,D,,,q1,1,,q2,X,D,,,q1,@,,q4,@,D,,,q1,X,,q1,X,E,,,q10,$,,q10,$,D,,,q10,1,,q10,1,D,,,q10,B,,q11,B,E,,,q10,S,,q10,S,D,,,q11,$,,q13,$,D,,,q11,1,,q12,S,E,,,q11,S,,q11,S,E,,,q11a,$,,q9,$,E,,,q11a,1,,q11a,1,E,,,q12,$,,q13,$,D,,,q12,1,,q12a,1,E,,,q12a,$,,q9,$,E,,,q12a,1,,q12a,1,E,,,q12a,S,,q11,S,E,,,q13,B,,qr,B,E,,,q13,S,,q13,S,D,,,q2,!,,q2!,!,D,,,q2,#,,q2,#,D,,,q2,1,,q2,1,D,,,q2,B,,q!,B,E,,,q2,X,,q2,X,D,,,q2!,1,,q2!,1,D,,,q2!,B,,qx2,1,D,,,q3,!,,q3,!,E,,,q3,#,,q1,#,E,,,q3,1,,q3,1,E,,,q3,X,,q4,X,E,,,q4,!,,q5,!,E,,,q4,#,,q4,#,D,,,q4,1,,q4,1,D,,,q4,B,,qf,B,D,,,q4,X,,q4,X,D,,,q5,#,,qi,#,E,,,q5,1,,q6,Y,D,,,q5,Y,,q5,Y,E,,,q6,!,,q6,!,D,,,q6,$,,q6$,$,D,,,q6,1,,q6,1,D,,,q6,B,,q$,B,E,,,q6,Y,,q6,Y,D,,,q6$,1,,q6$,1,D,,,q6$,B,,qy2,1,D,,,q7,!,,q5,!,E,,,q7,$,,q7,$,E,,,q7,1,,q7,1,E,,,q8,$,,q9,$,E,,,q8,1,,q8,1,D,,,q9,!,,qr,B,D,,,q9,1,,q10,S,D,,,q9,S,,q9,S,E,,,qc,!,,q8,!,D,,,qc,#,,qc,B,D,,,qc,$,,qc,B,D,,,qc,1,,qc,B,D,,,qc,B,,qc,B,D,,,qc,S,,qc,B,D,,,qc,X,,qc,B,D,,,qc,Y,,qc,B,D,,,qc1,!,,qc1,B,D,,,qc1,#,,qc1,B,D,,,qc1,$,,qc1,B,D,,,qc1,1,,qc1,1,D,,,qc1,B,,qf,B,D,,,qc1,S,,qc1,B,D,,,qc1,X,,qc1,B,D,,,qc1,Y,,qc1,B,D,,,qi,!,,qi,!,E,,,qi,#,,qi,#,E,,,qi,$,,qi,$,E,,,qi,1,,qi,1,E,,,qi,@,,qc,@,D,,,qi,B,,qi,B,E,,,qi,S,,qi,S,E,,,qi,X,,qi,X,E,,,qi,Y,,qi,Y,E,,,qi1,!,,qc1,B,D,,,qi1,#,,qi1,#,E,,,qi1,$,,qi1,$,E,,,qi1,1,,qi1,1,E,,,qi1,@,,qf,@,D,,,qi1,B,,qi1,B,E,,,qi1,S,,qi1,S,E,,,qi1,X,,qi1,X,E,,,qi1,Y,,qi1,Y,E,,,qr,!,,qr,B,D,,,qr,$,,qr,B,D,,,qr,1,,qr,B,D,,,qr,B,,qi1,B,E,,,qr,S,,qr,B,D,,,qrf,!,,qr,B,D,,,qrf,$,,qr,B,D,,,qrf,1,,qr,B,D,,,qrf,B,,qf,B,D,,,qrf,S,,qr,B,D,,,qx1,B,,qx2,1,D,,,qx2,B,,qx3,1,D,,,qx3,B,,q3,1,E,,,qy1,B,,qy2,1,D,,,qy2,B,,q7,1,E,,,
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