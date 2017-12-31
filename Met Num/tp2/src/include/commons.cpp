#include "commons.h"

int niter = 500;


void resolver(string pathEntrada, string pathSalida) {
    inputFile ifile = read_inputfile(pathEntrada);
    pair<MatrixXd, VectorXd> imAndMu = imagenesYesperanza(ifile);
    MatrixXd imagenes = MatrixXd(imAndMu.first);
    bool metodoDeEleccion = false; //true = kVecinos //false = centroDeMasa
    MatrixXd centroDeMasas(ifile.peopleCount, ifile.mainComponentsCount);
    pair<MatrixXd, vector<double>> autos;

    if (ifile.pxRows * ifile.pxCols > ifile.peopleCount * ifile.imagesPerPeopleCount)
    {
        MatrixXd m = matrizCovarianza_X_XT(imAndMu);
        autos = entrenamientoEficiente(imAndMu.first.transpose(), m, ifile.mainComponentsCount);
    }
    else
    {
        MatrixXd M = matrizCovarianza_XT_X(imAndMu);
        autos = entrenamiento(M, ifile.mainComponentsCount);
    }

    MatrixXd coordenadas = tcMat(autos.first, imagenes);
    int test;
    for (int i = 0; i < ifile.ntest.size(); ++i)
    {
        VectorXd imagenParaComparar = matrixToVector(readPGM(ifile.ntest[i].first));
        VectorXd vectorParaComparar = tc(autos.first, imagenParaComparar);
        if (metodoDeEleccion) {
            test = kVecinosMasCercanos(coordenadas, vectorParaComparar, 10, ifile.imagesPerPeopleCount);
        } 
        else {
             centroDeMasas = dameCentroDeMasa(coordenadas, ifile.imagesPerPeopleCount, ifile.peopleCount, ifile.mainComponentsCount);
             test = dameCentroMasCercano(vectorParaComparar, centroDeMasas);
        }
        int persona = ifile.ntest[i].second;
        writeFile(pathSalida, autos.second);
    }
}

MatrixXd dameCentroDeMasa(MatrixXd matrizTC, int imagenXpers, int cantPersonas, int cantCoordenadas){
    MatrixXd matrizMasas = MatrixXd::Zero(cantPersonas, cantCoordenadas);
    for (int i = 0; i < cantPersonas; ++i)
    {
        for (int j = i*imagenXpers ; j < i*imagenXpers + imagenXpers; ++j){
            matrizMasas.row(i) = matrizMasas.row(i) + matrizTC.row(j);
        }
    }
    matrizMasas = matrizMasas/imagenXpers;
    return matrizMasas;
}

int dameCentroMasCercano(VectorXd vectorNuevo, MatrixXd matrizMasas){
    VectorXd vectorAux = VectorXd::Zero(matrizMasas.cols());
    int distanciaRes;
    int respuesta;
    int distanciaAux;
    for (int i = 0; i < matrizMasas.rows(); ++i) {
        vectorAux = (matrizMasas.row(i)).transpose() - vectorNuevo;
        distanciaAux = vectorAux.norm();    
        if(i == 0 || distanciaAux < distanciaRes){
            distanciaRes = distanciaAux;
            respuesta = i;
        } 
    }
    return respuesta+1;
}

pair<double, VectorXd> metodoPotencia(MatrixXd B, VectorXd x) {
    VectorXd v = x;
    double lambda = 0;
    double lambdaAnterior = 0;
    VectorXd Bv;

    for (int i = 0; i < niter; ++i)
    {
        Bv = (B * v);
        v = Bv / Bv.norm();

        lambda = (v.transpose() * Bv)[0] / (v.transpose() * v)[0];

        if (i > 0 && abs(lambda - lambdaAnterior) <= EPS)
            return make_pair(lambda, v);

        lambdaAnterior = lambda;
    }
    return make_pair(lambda, v);
}

MatrixXd deflacion(MatrixXd B, pair<double, VectorXd> autos) {
    double lambda = autos.first;
    VectorXd v = autos.second;
    return B - (lambda * v * v.transpose());
}

pair<MatrixXd, vector<double>> entrenamiento(MatrixXd M, int cantAutovectores) {
    MatrixXd autovectores = MatrixXd::Zero(M.rows(), cantAutovectores);
    vector<double> autovalores;

    VectorXd v = VectorXd::Random(M.rows());
    for (int j = 0; j < cantAutovectores; ++j)
    {
        pair<double, VectorXd> p = metodoPotencia(M, v);
        autovectores.col(j) = p.second;
        M = deflacion(M, p);
        autovalores.push_back(sqrt(p.first));
    }
    
    return make_pair(autovectores, autovalores);
}

pair<MatrixXd, vector<double>> entrenamientoEficiente(MatrixXd Xt, MatrixXd m, int cantAutovectores) {
    MatrixXd autovectoresM = MatrixXd::Zero(Xt.rows(), cantAutovectores);
    vector<double> autovalores;

    VectorXd v = VectorXd::Random(m.rows());
    for (int j = 0; j < cantAutovectores; ++j)
    {
        pair<double, VectorXd> p = metodoPotencia(m, v);
        m = deflacion(m, p);
        double autovalor = sqrt(p.first);
        autovalores.push_back(autovalor);

        double sigma = sqrt(autovalor);
        autovectoresM.col(j) = Xt * p.second / sigma;
    }
    
    return make_pair(autovectoresM, autovalores);
}

MatrixXd tcMat(MatrixXd autovectores, MatrixXd imagenes) {
    return imagenes * autovectores;
}

VectorXd tc(MatrixXd autovectores, VectorXd imagen) {
    return imagen.transpose() * autovectores;
}

inputFile read_inputfile(string filePath) {
    inputFile inputFile1;

    ifstream file(filePath);
    string str;
    int pxRows, pxCols, peopleCount, imagesPerPeopleCount, mainComponentsCount, image, num;
    string pathDirectory = "";
    string imagePath = "";
    string imageFile = "";

    if (getline(file, str)) {
        istringstream ss(str);
        if (ss >> pathDirectory >> pxRows >> pxCols >> peopleCount >> imagesPerPeopleCount >> mainComponentsCount)
        {
            inputFile1.pxRows = pxRows;
            inputFile1.pxCols = pxCols;
            inputFile1.peopleCount = peopleCount;
            inputFile1.imagesPerPeopleCount = imagesPerPeopleCount;
            inputFile1.mainComponentsCount = mainComponentsCount;

            vector<vector<string> > imagesPaths(peopleCount, vector<string>(imagesPerPeopleCount, ""));
            for (int i = 0; i < peopleCount; ++i)
            {
                if (getline(file, str)) {
                    istringstream ss(str);
                    ss >> imagePath;
                    for (int j = 0; j < imagesPerPeopleCount; ++j)
                    {
                        ss >> imageFile;

                        stringstream ss2;
                        ss2 << pathDirectory << imagePath << imageFile << ".pgm";
                        string s = ss2.str();
                        imagesPaths[i][j] = s;
                    }
                }
            }
            inputFile1.imagesPaths = imagesPaths;

            vector<pair<string, int> > ntest;
            while (getline(file, str)) {
                istringstream ss(str);
                if (ss >> imagePath >> num) {
                    ntest.push_back(make_pair(imagePath, num));
                }
            }
            inputFile1.ntest = ntest;
        }
    }
    file.close();
    return inputFile1;
}

VectorXd matrixToVector(MatrixXd mat) {
    int n = mat.rows();
    int m = mat.cols();

    VectorXd vAux(n * m);
    int subIndex = 0;

    for (int k = 0; k < mat.rows(); ++k)
    {
        for (int l = 0; l < mat.cols(); ++l)
        {
            vAux[subIndex] = mat(k, l);
            subIndex++;
        }
    }
    return vAux;
}

pair<MatrixXd, VectorXd> imagenesYesperanza(inputFile ifile) {
    int cantImagenes = ifile.peopleCount * ifile.imagesPerPeopleCount;
    MatrixXd X = MatrixXd::Zero(cantImagenes, ifile.pxRows * ifile.pxCols);
    VectorXd mu = VectorXd::Zero(ifile.pxRows * ifile.pxCols);

    int index = 0;
    
    for (int i = 0; i < ifile.imagesPaths.size(); ++i)
    {
        for (int j = 0; j < ifile.imagesPaths[i].size(); ++j)
        {
            MatrixXd mAux = readPGM(ifile.imagesPaths[i][j]);
            VectorXd vAux = matrixToVector(mAux);

            mu += vAux;

            X.row(index) = vAux.transpose();
            index++;
        }
    }
    mu = mu / cantImagenes;

    return make_pair(X, mu);
}

bool pairCompare(const std::pair<int, double>& firstElem, const std::pair<int, double>& secondElem) {
  return firstElem.second < secondElem.second;
}

bool reconocerUnaCara(MatrixXd matrizCoordenadas, VectorXd imagenARecnocer){

    int cantidadImagenes = matrizCoordenadas.rows();
    int cantidadCoordenadas = matrizCoordenadas.cols();
    cout << "imagenes: " << cantidadImagenes << ", Coordenadas: " << cantidadCoordenadas << endl;
    VectorXd coordenadasPromedio = VectorXd::Zero(cantidadCoordenadas);

    for (int i = 0; i < cantidadImagenes; ++i)
    {
        coordenadasPromedio += matrizCoordenadas.row(i);
    }

    coordenadasPromedio = coordenadasPromedio / cantidadImagenes;


    double normaMax;
    double normaAux;
    VectorXd vectorAux;

    for (int i = 0; i < cantidadImagenes; ++i) {
            vectorAux = coordenadasPromedio - matrizCoordenadas.row(i).transpose();     
            normaAux = vectorAux.norm();        
            if (i == 0) {        
                normaMax = normaAux;            
            } else if (normaMax < normaAux) { 
                    normaMax = normaAux;           
            }       
    }

    vectorAux = coordenadasPromedio - imagenARecnocer;
    normaAux = vectorAux.norm();

    return normaAux <= normaMax;
}




void writeFile(string path, vector<double> autovalores) { 
    ofstream myfile;
    myfile.open(path);
    for (int i = 0; i < autovalores.size(); ++i)
    {
        myfile.precision(6);
        myfile << fixed;
        myfile << autovalores[i] << endl;
    }
    myfile.close();
}

MatrixXd matrizCovarianza_XT_X(pair<MatrixXd, VectorXd> xAndMu) {
    MatrixXd * X = &(xAndMu.first);

    int n = X->rows();
    VectorXd vectorUnos = VectorXd::Ones(n);
    MatrixXd matrizMu = vectorUnos * xAndMu.second.transpose();
    (*X) = ((*X) - matrizMu) / sqrt(n - 1);
    return (*X).transpose() * (*X);
}

MatrixXd matrizCovarianza_X_XT(pair<MatrixXd, VectorXd> xAndMu) {
    MatrixXd * X = &(xAndMu.first);

    int n = X->rows();
    VectorXd vectorUnos = VectorXd::Ones(n);
    MatrixXd matrizMu = vectorUnos * xAndMu.second.transpose();
    (*X) = ((*X) - matrizMu) / sqrt(n - 1);
    return (*X) * (*X).transpose();
}

int kVecinosMasCercanos(MatrixXd matrizTC, VectorXd imagenuevaTC, uint k, int imagenesPorPersona) {
    double normaMin;
    double normaAux;
    int imagen = 0;
    vector<pair<int, double> > vecinos;
    vector<pair<int, double> > vecinosRespuesta;
    VectorXd vectorAux;

    if (k > matrizTC.rows()) {
        cout << "k debe ser menor o igual a n" << endl;
    }
    else if (k != 1) {
        for (int i = 0; i < matrizTC.rows(); ++i) {
            vectorAux = imagenuevaTC - matrizTC.row(i).transpose();
            normaAux = vectorAux.norm();
            int persona = 1 + (int)(i / imagenesPorPersona);
            vecinos.push_back(make_pair(persona, normaAux));
        }
        sort(vecinos.begin(), vecinos.end(), pairCompare);
        for (int j = 0; j < k; j++) {
            vecinosRespuesta.push_back(vecinos[j]);
        }
    }
    else {
        for (int i = 0; i < matrizTC.rows(); ++i) {
            vectorAux = imagenuevaTC - matrizTC.row(i).transpose();     
            normaAux = vectorAux.norm();        
            if (i == 0) {        
                normaMin = normaAux;            
            }       
            else {
                if (normaMin > normaAux) {      
                    normaMin = normaAux;        
                    imagen = i;     
                }       
            }
        }

        int persona = 1 + (int)(imagen / imagenesPorPersona);

        vecinosRespuesta.push_back(make_pair(persona, normaMin));
    }

    map<int,double> mapVotacion;
    for (int i = 0; i < k; ++i)
    {
        int participante = vecinosRespuesta[i].first;
        double distancia = vecinosRespuesta[i].second;
        if (distancia==0) return participante;
        double ponderacion = 1 / ( distancia * distancia);

        pair<map<int,double>::iterator,bool> ret = mapVotacion.insert(pair<int,double>(participante, ponderacion));
        if(ret.second==false){
            ret.first->second+=ponderacion;
        }
    }

    map<int,double>::iterator it = mapVotacion.begin();
    int select = it->first;
    double selectBy = it->second;
    ++it;
    while ( it != mapVotacion.end()){
        if(it->second > selectBy){
            select = it->first;
            selectBy = it->second;
        }
        ++it;
    }

    return select;
}
