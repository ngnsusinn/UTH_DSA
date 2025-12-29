#include<bits/stdc++.h>

using namespace std;

 struct nhanVien{
    string maNhanVien; 
    string hoTen;
    string ngaySinh;
    string email;
    string diaChi;
    string soDienThoai;
    float soNgayCong;
    float luongNgay;
    float luongThucNhan;
 };

struct Node {
    nhanVien Data;
    Node* pNext;
};

typedef Node* List;

List danhSachNV = NULL;

Node* create_node(nhanVien x) {
    Node* p = new Node;
    if (p == NULL) return NULL;
    p->Data = x;
    p->pNext = NULL;
    return p;
}

void InitList() {
    danhSachNV = NULL;
}

void add_tail(nhanVien x) {
    Node* p = create_node(x);
    if (p == NULL) return;
    if (danhSachNV == NULL) {
        danhSachNV = p;
    }
    else {
        Node* q = danhSachNV;
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

void addAnEmployee(nhanVien& nv) {
    bool isDuplicate;
    do {
        cout << "Nhap ma nhan vien: ";
        cin >> nv.maNhanVien;
        isDuplicate = false;
        Node* p = danhSachNV;
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

void input_list(int n){
    nhanVien nv;
    for(int i = 0; i < n; i++){
        cout << "\nNhap thong tin nhan vien thu " << i + 1 << ":\n";
        addAnEmployee(nv);
        add_tail(nv);
    }
}

void write_to_file(const string& filename) {
    ofstream file(filename, ios::trunc);
    if (!file.is_open()) {
        cout << "Khong the mo file de ghi!\n";
        return;
    }
    Node* p = danhSachNV;
    while (p != NULL) {
        file << p->Data.maNhanVien << "," << p->Data.hoTen << "," << p->Data.ngaySinh << ","
            << p->Data.email << "," << p->Data.diaChi << "," << p->Data.soDienThoai << ","
            << p->Data.soNgayCong << "," << p->Data.luongNgay << "," << p->Data.luongThucNhan << endl;
        p = p->pNext;
    }
    file.close();
    cout << "Da ghi danh sach vao file " << filename << " thanh cong!\n";
}

nhanVien parseNhanVien(const string& line) {
    nhanVien nv;
    stringstream ss(line);
    string token;
    getline(ss, nv.maNhanVien, ',');
    getline(ss, nv.hoTen, ',');
    getline(ss, nv.ngaySinh, ',');
    getline(ss, nv.email, ',');
    getline(ss, nv.diaChi, ',');
    getline(ss, nv.soDienThoai, ',');
    getline(ss, token, ','); nv.soNgayCong = stof(token); //stof: convert string to float
    getline(ss, token, ','); nv.luongNgay = stof(token);
    getline(ss, token, ','); nv.luongThucNhan = stof(token);
    return nv;
}

void read_from_file(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Khong the mo file de doc!\n";
        return;
    }
    string line;
    while (getline(file, line)) {
        add_tail(parseNhanVien(line));
    }
    file.close();
    cout << "Da doc danh sach tu file " << filename << " thanh cong!\n";
}

void print_header() {
    cout << left << setw(15) << "Ma NV" << setw(25) << "Ho Ten" << setw(15) << "Ngay Sinh"
         << setw(30) << "Email" << setw(30) << "Dia Chi" << setw(15) << "So DT"
         << setw(15) << "Ngay Cong" << setw(15) << "Luong Ngay" << setw(20) << "Luong Thuc Nhan" << endl;
    cout << string(180, '-') << endl;
}

void print_nhanVien(const nhanVien& nv) {
    cout << left << setw(15) << nv.maNhanVien 
         << setw(25) << nv.hoTen 
         << setw(15) << nv.ngaySinh
         << setw(30) << nv.email 
         << setw(35) << nv.diaChi 
         << setw(15) << nv.soDienThoai
         << setw(15) << nv.soNgayCong 
         << setw(15) << fixed << setprecision(0) << nv.luongNgay 
         << setw(20) << nv.luongThucNhan << endl;
}

void view_list(List l = danhSachNV) {
    if (l == NULL) {
        cout << "Danh sach nhan vien rong!\n";
        return;
    }
    print_header();
    Node* p = l;
    while (p != NULL) {
        print_nhanVien(p->Data);
        p = p->pNext;
    }
}

void find_nhanVien_by_maNV(const string& maNV) {
    Node* p = danhSachNV;
    while (p != NULL) {
        if (p->Data.maNhanVien == maNV) {
            cout << "Nhan vien tim thay:\n";
            print_header();
            print_nhanVien(p->Data);
            return;
        }
        p = p->pNext;
    }
    cout << "Khong tim thay nhan vien voi ma: " << maNV << endl;
}

string toLower(const string& s) {
    string result = s;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

void find_nhanVien_by_hoTen(const string& hoTen) {
    Node* p = danhSachNV;
    bool found = false;
    string searchLower = toLower(hoTen);
    while (p != NULL) {
        if (toLower(p->Data.hoTen).find(searchLower) != string::npos) {
            if (!found) {
                cout << "Nhan vien tim thay:\n";
                print_header();
                found = true;
            }
            print_nhanVien(p->Data);
        }
        p = p->pNext;
    }
    if (!found) {
        cout << "Khong tim thay nhan vien voi ho ten chua: " << hoTen << endl;
    }
}

void find_nhanVien_luongThapNhat() {
    if (danhSachNV == NULL) {
        cout << "Danh sach nhan vien rong!\n";
        return;
    }
    
    float minLuong = danhSachNV->Data.luongThucNhan;
    Node* p = danhSachNV->pNext;
    while (p != NULL) {
        if (p->Data.luongThucNhan < minLuong) {
            minLuong = p->Data.luongThucNhan;
        }
        p = p->pNext;
    }
    
    cout << "Nhan vien co luong thuc nhan thap nhat (" << fixed << setprecision(0) << minLuong << "):\n";
    print_header();
    p = danhSachNV;
    while (p != NULL) {
        if (p->Data.luongThucNhan == minLuong) {
            print_nhanVien(p->Data);
        }
        p = p->pNext;
    }
}

void menu() {
    cout << "\n============== QUAN LY NHAN VIEN ==============\n";
    cout << "1. Nhap danh sach nhan vien tu ban phim\n";
    cout << "2. Doc va xuat danh sach nhan vien tu file\n";
    cout << "3. Tim kiem nhan vien theo ma nhan vien\n";
    cout << "4. Tim kiem nhan vien theo ten\n";
    cout << "5. Xuat nhan vien co luong thuc linh thap nhat\n";
    cout << "0. Thoat\n";
    cout << "===============================================\n";
    cout << "Chon chuc nang: ";
}

int main() {
    int choice;
    int n;
    string maNV, hoTen;
    
    do {
        menu();
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1:
                cout << "Nhap so luong nhan vien: ";
                cin >> n;
                cin.ignore();
                InitList();
                input_list(n);
                write_to_file("DSNV.txt");
                break;
                
            case 2:
                InitList();
                read_from_file("DSNV.txt");
                cout << "\nDanh sach nhan vien:\n";
                view_list();
                break;
                
            case 3:
                cout << "Nhap ma nhan vien can tim: ";
                getline(cin, maNV);
                find_nhanVien_by_maNV(maNV);
                break;
                
            case 4:
                cout << "Nhap ten nhan vien can tim: ";
                getline(cin, hoTen);
                find_nhanVien_by_hoTen(hoTen);
                break;
                
            case 5:
                find_nhanVien_luongThapNhat();
                break;
                
            case 0:
                cout << "Tam biet!\n";
                break;
                
            default:
                cout << "Lua chon khong hop le! Vui long chon lai.\n";
        }
    } while (choice != 0);
    
    return 0;
}