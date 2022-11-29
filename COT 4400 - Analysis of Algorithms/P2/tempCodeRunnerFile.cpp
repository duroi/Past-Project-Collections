  else if (k != t.size() && i == x.size() ) {
        cout <<"4: "<< i << ":" << j<< ":" << k << endl;
        solutions[x.size() - i][y.size() - j - 1] = temp1 + op1;
    }
    else if (k != t.size() && j == y.size()) {
        cout <<"5: "<< i << ":" << j<< ":" << k << endl;
        solutions[x.size() - i - 1][y.size() - j] = temp2 + op2;

    }
    else {
        cout <<"6: "<< i << ":" << j<< ":" << k << endl;
    }