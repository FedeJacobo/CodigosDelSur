template <class A>
class Nodo {
public:
A arco;
Nodo<A>(const A &a) : arco(a) {}
virtual ~Nodo() {}
};
