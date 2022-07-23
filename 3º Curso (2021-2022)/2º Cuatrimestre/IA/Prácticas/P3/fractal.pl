fractal :-
    new(D, window('Fractal')),
    send(D, size, size(800, 600)),
    drawTree(D, 400, 500, 0, 3),
    send(D, open).

drawTree(_D, _X, _Y, _Angle, 0).

drawTree(D, X1, Y1, Angle, Depth) :-
    De is Depth - 1,
    X2 is X1 + cos(Angle * pi / 180.0) * Depth * 10.0,
    Y2 is Y1 + sin(Angle * pi / 180.0) * Depth * 10.0,
    new(Line, line(X1, Y1, X2, Y2, none)),
    send(D, display, Line),
    A1 is Angle - 60,
    drawTree(D, X2, Y2, A1, De),
    X3 is X2 + cos(-Angle * pi / 180.0) * Depth * 10.0,
    Y3 is Y2 + sin(-Angle * pi / 180.0) * Depth * 10.0,
    new(Line2, line(X2, Y2, X3, Y3, none)),
    send(D, display, Line2),
    A2 is Angle + 60,
    drawTree(D, X3, Y3, A2, De),
    X4 is X3 + cos(0 * pi / 180.0) * Depth * 10.0,
    Y4 is Y3 + sin(0 * pi / 180.0) * Depth * 10.0,
    new(Line3, line(X3, Y3, X4, Y4, none)),
    send(D, display, Line3),
    A3 is Angle,
    drawTree(D, X4, Y4, A3, De).
