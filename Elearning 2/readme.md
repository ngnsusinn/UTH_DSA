# Hệ thống Quản lý Nhân viên
Chương trình quản lý thông tin nhân viên sử dụng danh sách liên kết đơn (Singly Linked List) trong C++.

## Các cấu trúc dữ liệu có trong bài

### 1. Cấu trúc `nhanVien`
Lưu các thông tin của nhân viên:

```cpp
struct nhanVien{
    string maNhanVien;      // Mã nhân viên (duy nhất)
    string hoTen;           // Họ và tên
    string ngaySinh;        // Ngày sinh (định dạng "dd/mm/yyyy")
    string email;           // Địa chỉ email
    string diaChi;          // Địa chỉ liên hệ
    string soDienThoai;     // Số điện thoại
    float soNgayCong;       // Số ngày công (0-31)
    float luongNgay;        // Lương mỗi ngày
    float luongThucNhan;    // Lương thực nhận = soNgayCong * luongNgay
}
```

### 2. Cấu trúc `Node`
Node trong danh sách liên kết:
```cpp
struct Node {
    nhanVien Data;    // Dữ liệu nhân viên
    Node* pNext;      // Con trỏ đến node tiếp theo
};
```

### 3. Biến toàn cục
```cpp
List danhSachNV = NULL;  // Danh sách nhân viên toàn cục
```

## Menu chương trình

```
============== QUAN LY NHAN VIEN ==============
1. Nhap danh sach nhan vien tu ban phim
2. Doc va xuat danh sach nhan vien tu file
3. Tim kiem nhan vien theo ma nhan vien
4. Tim kiem nhan vien theo ten
5. Xuat nhan vien co luong thuc linh thap nhat
0. Thoat
===============================================
```

## Các chức năng chính

### 1. Khởi tạo và quản lý danh sách
| Hàm | Mô tả |
|-----|-------|
| `InitList()` | Khởi tạo danh sách rỗng (dùng biến toàn cục) |
| `create_node(nhanVien x)` | Tạo node mới chứa thông tin nhân viên |
| `add_tail(nhanVien x)` | Thêm nhân viên vào cuối danh sách |

### 2. Xác thực dữ liệu
| Hàm | Mô tả |
|-----|-------|
| `isLeapYear(int year)` | Kiểm tra năm nhuận |
| `isValidDate(const string& date)` | Kiểm tra tính hợp lệ của ngày tháng |

### 3. Nhập dữ liệu
| Hàm | Mô tả |
|-----|-------|
| `addAnEmployee(nhanVien& nv)` | Nhập thông tin một nhân viên với xác thực |
| `input_list(int n)` | Nhập danh sách n nhân viên |

### 4. Đọc/Ghi file
| Hàm | Mô tả |
|-----|-------|
| `write_to_file(const string& filename)` | Ghi danh sách vào file CSV |
| `read_from_file(const string& filename)` | Đọc danh sách từ file CSV |
| `parseNhanVien(const string& line)` | Parse một dòng CSV thành struct nhanVien |

### 5. Hiển thị dữ liệu
| Hàm | Mô tả |
|-----|-------|
| `print_header()` | In header bảng danh sách |
| `print_nhanVien(const nhanVien& nv)` | In thông tin một nhân viên |
| `view_list(List l = danhSachNV)` | Hiển thị toàn bộ danh sách (mặc định dùng biến toàn cục) |

### 6. Tìm kiếm
| Hàm | Mô tả |
|-----|-------|
| `toLower(const string& s)` | Chuyển chuỗi về chữ thường |
| `find_nhanVien_by_maNV(const string& maNV)` | Tìm nhân viên theo mã (chính xác) |
| `find_nhanVien_by_hoTen(const string& hoTen)` | Tìm nhân viên theo tên (không phân biệt hoa thường, tìm chuỗi con) |
| `find_nhanVien_luongThapNhat()` | Tìm và hiển thị nhân viên có lương thấp nhất |

## Luồng nhập dữ liệu

1. **Nhập mã nhân viên** - Kiểm tra trùng lặp, yêu cầu nhập lại nếu đã tồn tại
2. **Nhập họ tên** - Cho phép nhập có dấu cách
3. **Nhập ngày sinh** - Xác thực định dạng dd/mm/yyyy và tính hợp lệ
4. **Nhập email** - Chuỗi ký tự tự do
5. **Nhập địa chỉ** - Chuỗi ký tự tự do
6. **Nhập số điện thoại** - Chuỗi số
7. **Nhập số ngày công** - Số thực từ 0 đến 31
8. **Nhập lương ngày** - Số thực >= 0
9. **Tính lương thực nhận** - Tự động: `luongThucNhan = soNgayCong * luongNgay`

## Các quy tắc xác thực

### Mã nhân viên
- Phải duy nhất trong danh sách
- Tự động kiểm tra và yêu cầu nhập lại nếu trùng

### Ngày sinh
- Định dạng bắt buộc: dd/mm/yyyy (VD: 25/12/2000)
- Ngày phải hợp lệ theo tháng và năm
- Tháng 2: 28 ngày (29 nếu năm nhuận)
- Tháng 4, 6, 9, 11: 30 ngày
- Các tháng còn lại: 31 ngày
- Năm hợp lệ: 1 - 2025

### Số ngày công
- Giá trị: 0 - 31
- Kiểu dữ liệu: float (cho phép nửa ngày công)

### Lương ngày
- Giá trị: >= 0
- Kiểu dữ liệu: float

## Thuật toán tìm kiếm

### Tìm theo họ tên (không phân biệt hoa thường)
```cpp
string toLower(const string& s) {
    string result = s;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// So sánh: toLower(hoTen).find(searchLower) != string::npos
```

### Tìm nhân viên lương thấp nhất
1. **Lần duyệt 1**: Tìm giá trị lương thực nhận nhỏ nhất
2. **Lần duyệt 2**: In ra tất cả nhân viên có lương bằng giá trị nhỏ nhất

## Công thức tính toán

```
Lương thực nhận = Số ngày công × Lương ngày
```

## Cấu trúc file dữ liệu (CSV)

File mặc định: `DSNV.txt`

Mỗi dòng trong file chứa thông tin của một nhân viên với các trường được phân cách bởi dấu phẩy:

```
maNhanVien,hoTen,ngaySinh,email,diaChi,soDienThoai,soNgayCong,luongNgay,luongThucNhan
```

**Ví dụ:**
```
NV001,Nguyen Van An,15/03/1990,an.nguyen@email.com,123 Le Loi Q1 TPHCM,0901234567,25,500000,12500000
NV002,Tran Thi Binh,22/07/1995,binh.tran@email.com,456 Nguyen Hue Q1 TPHCM,0912345678,28,450000,12600000
```

## Hướng dẫn sử dụng

1. Biên dịch chương trình:
```bash
g++ main.cpp -o employee_manager
```

2. Chạy chương trình:
```bash
./employee_manager
```

3. Chọn chức năng từ menu:
   - **Option 1**: Nhập nhân viên từ bàn phím → tự động lưu vào DSNV.txt
   - **Option 2**: Đọc từ DSNV.txt → hiển thị danh sách
   - **Option 3**: Tìm theo mã nhân viên (VD: NV001)
   - **Option 4**: Tìm theo tên (VD: "nguyen", "an") - không phân biệt hoa thường
   - **Option 5**: Xem nhân viên có lương thấp nhất
   - **Option 0**: Thoát chương trình

## Dữ liệu mẫu

File `DSNV.txt` chứa 10 nhân viên mẫu với các mức lương khác nhau. Nhân viên NV005 và NV009 có lương thấp nhất (7,800,000).

## Lưu ý

- Chương trình sử dụng thư viện `bits/stdc++.h` (GNU C++)
- Dữ liệu được lưu trữ trong biến toàn cục `danhSachNV` dưới dạng danh sách liên kết
- Các hàm mặc định sử dụng biến toàn cục, không cần truyền tham số
- File xuất ra có định dạng CSV, có thể mở bằng Excel hoặc text editor
- Tất cả các trường nhập liệu đều có xác thực để đảm bảo tính hợp lệ
- Tìm kiếm theo tên hỗ trợ tìm chuỗi con và không phân biệt chữ hoa/thường