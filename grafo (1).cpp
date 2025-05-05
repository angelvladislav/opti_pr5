 /*
 *  GRAFO.CPP - Plantilla para la implementaci�n de la clase GRAFOS
 *
 *
 *               Autores : Angel Vladislav Alonso Yemelyantseva
 *               Correo : alu0101489827
 *               Cursos  : 2024-25
 */

 #include "grafo.h"

 void GRAFO :: destroy()
 {
     for (unsigned i=0; i< n; i++)
     {
         LS[i].clear();
         if (dirigido == 1)
                LP[i].clear();
     }
     LS.clear();
     if (dirigido == 1)
         LP.clear();
 
 }
 
 void GRAFO :: build (char nombrefichero[85], int &errorapertura)
 {
     ElementoLista     dummy;
     ifstream textfile;
     textfile.open(nombrefichero);
     if (textfile.is_open())
     {
         unsigned i, j, k;
         // leemos por conversion implicita el numero de nodos, arcos y el atributo dirigido
         textfile >> (unsigned &) n >> (unsigned &) m >> (unsigned &) dirigido;
         // los nodos internamente se numeran desde 0 a n-1
         // creamos las n listas de sucesores
         LS.resize(n);
         // leemos los m arcos
         for (k=0;k<m;k++)
             {
             textfile >> (unsigned &) i  >> (unsigned &) j >> (int &) dummy.c;
             //restamos 1 a los indices para quitar problemas de acceso a memoria
             i--;
             j--;
             //damos los valores a dummy.j y dummy.c
             dummy.j = j;
             //situamos en la posici�n del nodo i a dummy mediante push_back
             LS[i].push_back(dummy);
             //pendiente de hacer un segundo push_back si es no dirigido. O no.
             if (!dirigido){
                dummy.j = i;
                LS[j].push_back(dummy);
             }
         }
             //pendiente la construcci�n de LP, si es dirigido
             if (dirigido){
                ListaPredecesores();
             }
             //pendiente del valor a devolver en errorapertura
         errorapertura = 0;
     } else  {
         errorapertura = 1;
     }
 }
 
 GRAFO::~GRAFO()
 {
     destroy();
 }
 
 GRAFO::GRAFO(char nombrefichero[85], int &errorapertura)
 {
     build (nombrefichero, errorapertura);
 }
 
 void GRAFO:: actualizar (char nombrefichero[85], int &errorapertura)
 {
     //Limpiamos la memoria dinamica asumida en la carga previa, como el destructor
     destroy();
     //Leemos del fichero y actualizamos G con nuevas LS y, en su caso, LP
     build(nombrefichero, errorapertura);
 }
 
 unsigned GRAFO::Es_dirigido()
 {
    return dirigido;
 }
 
 void GRAFO::Info_Grafo()
 {
    if (dirigido){
        std::cout << "Este grado es DIRIGIDO" << std::endl;
        std::cout << "Tiene " << n << " nodos" << std::endl;
        std::cout << "Tiene " << m << " arcos" << std::endl;
    } else {
        std::cout << "Este grado es NO-DIRIGIDO" << std::endl;
        std::cout << "Tiene " << n << " nodos" << std::endl;
        std::cout << "Tiene " << m << " arcos" << std::endl; 
    }
 }
 
 void Mostrar_Lista(vector<LA_nodo> L)
 {
	for (unsigned i = 0; i < L.size(); i++) {
		std::cout << "Nodo " << i + 1 << ":";
		for (unsigned j = 0; j < L[i].size(); j++) {
			std::cout << " (" << L[i][j].j + 1 << ", " << L[i][j].c << ")";
		}
		std::cout << std::endl;
	}
 }

 void GRAFO :: Mostrar_Listas (int l)
 {
	if (l == 1){
		Mostrar_Lista(LS);
	} else if (l == -1){
		Mostrar_Lista(LP);
	}	else {
		Mostrar_Lista(LS);
	}
 }
 
 void GRAFO :: ListaPredecesores() //Recorre la lista de sucesores LS para construir la de predecesores, LP
 {
    LP.resize(n); 
    for (unsigned i=0;i<n;i++){
        for (unsigned j=0;j<LS[i].size();j++){
            ElementoLista dummy;
            dummy.j = i;
            dummy.c = LS[i][j].c;
            LP[LS[i][j].j].push_back(dummy);
        }
    }
 }
 
 void GRAFO::dfs_cc(unsigned i, vector<bool> &visitado) //Este recorrido esta� hecho adhoc para mostrar el ritmo de nodos visitados, para su uso en la construccion de Componentes Conexas
 {
    visitado[i] = true; //visitamos el nodo i+1
    cout << i+1;
    for (unsigned j=0;j<LS[i].size();j++) { //recorremos la adyacencia del    nodo visitado, esto es, i+1
        if (!visitado[LS[i][j].j]) {
        cout << " , ";
        dfs_cc(LS[i][j].j, visitado);
        }
    }
 }
 
 void GRAFO::ComponentesConexas()
 {
    unsigned i, componentesconexas = 0;
    vector<bool> visitado;
    visitado.resize(n,false);
    for (unsigned i = 0; i < n; i++) {
        if (visitado[i] == false) {
            componentesconexas++;
            cout << "Componente Conexa " << componentesconexas << " : {";
            dfs_cc(i, visitado);
            cout << "}" << endl;
        }
    }
 }
 
 ////////////////////////////////////////////////////////////////////////////

 void GRAFO::ComponentesConexasDirigido()
 {
    unsigned i, componentesconexas = 0;
    vector<bool> visitado;
    visitado.resize(n,false);
    for (unsigned i = 0; i < n; i++) {
        if (visitado[i] == false) {
            componentesconexas++;
            cout << "Componente Conexa " << componentesconexas << " : {";
            dfs_cc_dirigido(i, visitado);
            cout << "}" << endl;
        }
    }
 }


 void GRAFO::dfs_cc_dirigido(unsigned i, vector<bool> &visitado) //Este recorrido esta� hecho adhoc para mostrar el ritmo de nodos visitados, para su uso en la construccion de Componentes Conexas
 {
    visitado[i] = true; //visitamos el nodo i+1
    cout << i+1;
    for (unsigned j=0;j<LS[i].size();j++) { //recorremos la adyacencia del    nodo visitado, esto es, i+1
        if (!visitado[LS[i][j].j]) {
        cout << " , ";
        dfs_cc_dirigido(LS[i][j].j, visitado);
        }
    }
    for (unsigned j=0;j<LP[i].size();j++) {
        if (!visitado[LP[i][j].j]) {
        cout << " , ";
        dfs_cc_dirigido(LP[i][j].j, visitado);
        }
    }
 }

 ////////////////////////////////////////////////////////////////////////////

 void GRAFO::dfs_cfc(unsigned i, vector<bool> &visitado) //Este recorrido esta� hecho adhoc para mostrar el ritmo de nodos visitados, para su uso en la construccion de Componentes fuertemente Conexas
 {
    visitado[i] = true; 
    cout << i+1;
    for (unsigned j=0;j<LP[i].size();j++) { 
        if (!visitado[LP[i][j].j]) {
        cout << " , ";
        dfs_cfc(LP[i][j].j, visitado);
        }
    }
 }
 
 void GRAFO::dfs_postnum(unsigned i, vector<bool> &visitado, vector<unsigned> &postnum, unsigned &postnum_ind) //Este recorrido esta� hecho adhoc para calcular el orden postnumeraci�n de los nodos
 {
    visitado[i] = true;
    for (unsigned j = 0; j < LS[i].size(); j++) {
        if (!visitado[LS[i][j].j]) { 
            dfs_postnum(LS[i][j].j, visitado, postnum, postnum_ind);
        }
    }
    postnum[postnum_ind--] = i; 
 }
 
 void GRAFO::ComponentesFuertementeConexas()
 {
     unsigned postnum_ind, componentesfuertementeconexas = 0;
     vector<bool> visitado;
     vector<unsigned> postnum;
     visitado.resize(n, false);
     postnum.resize(n, UERROR);
     postnum_ind = n-1;

     for (unsigned i = 0; i < n; i++) {
         if (visitado[i] == false) {
             dfs_postnum(i, visitado, postnum, postnum_ind);
         }
     }

     visitado.clear();
     visitado.resize(n, false);
     for (unsigned i = 0; i < n; i++) {
         if (visitado[postnum[i]] == false) {
             componentesfuertementeconexas++;
             cout << "Componente Fuertemente Conexa " << componentesfuertementeconexas << " : {";
             dfs_cfc(postnum[i], visitado);
             cout << "}" << endl;
         }
     }
 }
 
 void GRAFO::Sollin() {

    // ------------------ INICIALIZACIÓN ------------------
    vector<unsigned> Raiz(n);
    vector<vector<unsigned>> N(n);

    for (unsigned i = 0; i < n; i++) {
        Raiz[i] = i;
        N[i].push_back(i);
    }

    unsigned iteracion = 1;

    // ------------------ BUCLE PRINCIPAL ------------------
    unsigned AristasAdd = 0;
    int peso_total = 0;

    while (AristasAdd < n - 1) {
        unsigned AristasPrevias = AristasAdd;
        cout << "......................................................" << endl;
        cout << "\tIteracion " << iteracion << endl;
        cout << "Los sub_arboles son :" << endl;

    // ------------------ ARBOLES ANTES DE ITERACIÓN ------------------
        for (unsigned i = 0; i < N.size(); i++) {
            if (!N[i].empty()) {
                cout << "el sub_arbol " << i + 1 << " tiene los nodos: ";
                for (unsigned j = 0; j < N[i].size(); j++) {
                    cout << "(" << N[i][j] + 1 << ", " << i + 1 << " ) ";
                }
                cout << endl;
            } else {
                cout << "el sub_arbol " << i + 1 << " ahora está vacío" << endl;
            }
        }
        cout << endl;

        // ------------------ VECINO-CERCANO(N[K], IJ, JK) ------------------
        for (unsigned k = 0; k < n; k++) {
            if (!N[k].empty()) {
                int mink = maxint;
                unsigned ik = UERROR;
                unsigned jk = UERROR;

                for (unsigned p = 0; p < N[k].size(); p++) {
                    unsigned i = N[k][p];
                    for (unsigned l = 0; l < LS[i].size(); l++) {
                        unsigned j = LS[i][l].j;
                        int c = LS[i][l].c;
                        if (Raiz[i] != Raiz[j] && c < mink) {
                            mink = c;
                            ik = i;
                            jk = j;
                        }
                    }
                }

                // ------------------ UNION(IJ, JK) ------------------
                if (ik != UERROR && jk != UERROR) {
                    cout << "Arista " << AristasAdd + 1 << " con peso " << mink << " añadida: (" << ik + 1 << ",  " << jk + 1 << ")" << endl;
                    peso_total += mink;
                    AristasAdd++;

                    unsigned NewRaiz = Raiz[ik];
                    unsigned OldRaiz = Raiz[jk];
                    if (NewRaiz > OldRaiz) {
                        NewRaiz = Raiz[jk];
                        OldRaiz = Raiz[ik];
                    }

                    for (unsigned i = 0; i < N[OldRaiz].size(); i++) {
                        unsigned nodo = N[OldRaiz][i];
                        Raiz[nodo] = NewRaiz;
                        N[NewRaiz].push_back(nodo);
                    }
                    N[OldRaiz].clear();
                }
            }
        }
        cout << "\n";

        // ------------------ ARBOLES DESPUES DE ITERACION ------------------
        cout << "Los sub_arboles son :" << endl;
        for (unsigned i = 0; i < N.size(); i++) {
            if (!N[i].empty()) {
                cout << "el sub_arbol " << i + 1 << " tiene: ";
                for (unsigned j = 0; j < N[i].size(); j++) {
                    cout << "(" << N[i][j] + 1 << ", " << i + 1 << " ) ";
                }
                cout << endl;
            } else {
                cout << "el sub_arbol " << i + 1 << " ahora está vacío" << endl;
            }
        }
        cout << endl;
        iteracion++;

        // ------------------ CRITERIO DE PARADA ------------------
        if (AristasPrevias == AristasAdd){
            break;
        }
        
    }
    if (AristasAdd == (n - 1)) {
        cout << "El peso/coste del árbol es: " << peso_total << endl;
        cout << "......................................................" << endl;
        return;
    } else {
        cout << "El grafo no es conexo" << endl;
        cout << "......................................................" << endl;
        return;
    }
}

void ImprimirMatrices(unsigned dim, unsigned k, const vector<vector<ElementoLista>> &P) {
    cout << "Iteración " << k << ":" << endl;
    cout << "Matriz de costes (D):" << endl;
    for (unsigned i = 0; i < dim; i++) {
        for (unsigned j = 0; j < dim; j++) {
            if (P[i][j].c == maxint) {
                cout << "INF\t";
            } else {
                cout << P[i][j].c << "\t";
            }
        }
        cout << endl;
    }

    cout << "Matriz de predecesores (Pred):" << endl;
    for (unsigned i = 0; i < dim; i++) {
        for (unsigned j = 0; j < dim; j++) {
            if (P[i][j].j == UERROR) {
                cout << "-\t"; 
            } else {
                cout << P[i][j].j + 1 << "\t";
            }
        }
        cout << endl;
    }

    cout << "----------------------------------------" << endl;
}

void GRAFO::Floyd_Warshall() {
    vector<vector<ElementoLista>> P;
    bool circuitoCostoNegativo = false; 

    P.resize(n);
    for (unsigned i = 0; i < n; i++) {
        P[i].resize(n);
    }

    for (unsigned i = 0; i < n; i++) {
        for (unsigned j = 0; j < n; j++) {
            if (i != j) {
                P[i][j].j = UERROR; 
                P[i][j].c = maxint;
            } else {
                P[i][j].j = i;
                P[i][j].c = 0; 
            }
        }
    }
    for (unsigned i = 0; i < n; i++) {
        for (unsigned l = 0; l < LS[i].size(); l++) {
            unsigned j = LS[i][l].j; 
            int c = LS[i][l].c; 
            P[i][j].j = i;
            P[i][j].c = c; 
        }
    }

    // Algoritmo de Floyd-Warshall
    for (unsigned k = 0; k < n; k++) {
        ImprimirMatrices(n, k, P);
        for (unsigned i = 0; i < n; i++) {
            if (i != k) {
                for (unsigned j = 0; j < n; j++) {
                    if (j != k) {
                        if (P[i][j].c > P[i][k].c + P[k][j].c && P[i][k].c != maxint && P[k][j].c != maxint) {
                            P[i][j].c = P[i][k].c + P[k][j].c;
                            P[i][j].j = P[k][j].j;
                        }
                    }
                }
            }
        }
    }

    ImprimirMatrices(n, n, P);

    for (unsigned i = 0; i < n; i++) {
        if (P[i][i].c < 0) {
            circuitoCostoNegativo = true;
            break;
        }
    }

    if (!circuitoCostoNegativo) {
        cout << "Caminos mínimos entre cada par de nodos:" << endl;
        for (unsigned i = 0; i < n; i++) {
            for (unsigned j = 0; j < n; j++) {
                if (P[i][j].c != maxint) {
                    cout << "De " << i + 1 << " a " << j + 1 << " -> Coste: " << P[i][j].c;
                    cout << ", Camino: ";
                    unsigned pred = j;
                    while (pred != i) {
                        cout << pred + 1 << " <- ";
                        pred = P[i][pred].j;
                    }
                    cout << i + 1 << endl;
                } else {
                    cout << "De " << i + 1 << " a " << j + 1 << " -> No hay camino" << endl;
                }
            }
        }
    } else {
        cout << "Hay circuitos de coste negativo" << endl;
    }
}