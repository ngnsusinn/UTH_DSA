#include<bits/stdc++.h>

using namespace std;

 struct nhanVien{
    string maNhanVien; // maNhanVien là duy nhất
    string hoTen;
    string ngaySinh; // ngaySinh có định dạng "dd/mm/yyyy"
    string email;
    string diaChi;
    string soDienThoai;
    float soNgayCong;
    float luongNgay;
    float luongThucNhan;
 }

struct Node {
    nhanVien Data;
    Node* pNext;
};

typedef Node* List;

Node* create_node(nhanVien x) {
    Node* p = new Node;
    if (p == NULL) return NULL;
    p->Data = x;
    p->pNext = NULL;
    return p;
}

void InitList(List& l) {
    l = NULL;
}

void add_tail(List& l, nhanVien x) {
    Node* p = create_node(x);
    if (p == NULL) return;
    if (l == NULL) {
        l = p;
    }
    else {
        Node* q = l;
        while (q->pNext != NULL) {
            q = q->pNext;
        }
        q->pNext = p;
    }
}

bool isLeapYear(int year){
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool isValidDate(const string& date){
    if(date.length() != 10 || date[2] != '/' || date[5] != '/') return false;
    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));
    if (year < 1 || year > 2025 || month < 1 || month > 12 || day < 1) return false;
    int maxDays;
    switch(month){
        case 2:
            maxDays = isLeapYear(year) ? 29 : 28;
            break;
        case 4: case 6: case 9: case 11:
            maxDays = 30;
            break;
        default:
            maxDays = 31;
    }
    return day <= maxDays;
}

void addAnEmployee(nhanVien& nv, List l) {
    bool isDuplicate;
    do {
        cout << "Nhap ma nhan vien: ";
        cin >> nv.maNhanVien;
        isDuplicate = false;
        Node* p = l;
        while(p != NULL){
            if(p->Data.maNhanVien == nv.maNhanVien){
                isDuplicate = true;
                cout << "Ma nhan vien da ton tai! Nhap lai: ";
                break;
            }
            p = p->pNext;
        }
    } while(isDuplicate);
    cin.ignore();
    cout << "Nhap ho ten: ";
    getline(cin, nv.hoTen);

    do{
        cout << "Nhap ngay sinh (theo dinh dang dd/mm/yyyy): ";
        getline(cin, nv.ngaySinh);
    }while(!isValidDate(nv.ngaySinh));

    cout << "Nhap email: ";
    getline(cin, nv.email);
    cout << "Nhap dia chi: ";
    getline(cin, nv.diaChi);
    cout << "Nhap so dien thoai : ";
    while(!(cin >> nv.soDienThoai)){
        cout << "So dien thoai khong hop le! Nhap lai: ";
        cin.clear();
        cin.ignore();
    }
    cin.ignore();

    cout << "Nhap so ngay cong: ";
    while(!(cin >> nv.soNgayCong) || nv.soNgayCong < 0 || nv.soNgayCong > 31){
        cout << "So ngay cong khong hop le (0-31)! Nhap lai: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    cout << "Nhap luong ngay: ";
    while (!(cin >> nv.luongNgay) || nv.luongNgay < 0) {
        cout << "Luong ngay khong hop le! Nhap lai: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    nv.luongThucNhan = nv.soNgayCong * nv.luongNgay;
    cin.ignore();
}

void input_list(List& l, int n){
    nhanVien nv;
    for(int i = 0; i < n; i++){
        cout << "\nNhap thong tin nhan vien thu " << i + 1 << ":\n";
        addAnEmployee(nv, l);
        add_tail(l, nv);
    }
}

void write_to_file(List l, const string& filename) {
    ofstream file(filename, ios::trunc);
    if (!file.is_open()) {
        cout << "Khong the mo file de ghi!\n";
        return;
    }
    Node* p = l;
    while (p != NULL) {
        file << p->Data.maNhanVien << "," << p->Data.hoTen << "," << p->Data.ngaySinh << ","
            << p->Data.email << "," << p->Data.diaChi << "," << p->Data.soDienThoai << ","
            << p->Data.soNgayCong << "," << p->Data.luongNgay << "," << p->Data.luongThucNhan << endl;
        p = p->pNext;
    }
    file.close();
    cout << "Da ghi danh sach vao file " << filename << " thanh cong!\n";
}