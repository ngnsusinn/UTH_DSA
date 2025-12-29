## Các cấu trúc dữ liệu có trong bài
 - ```nhanVien``` : Lưu các thông tin của nhân viên bao gồm mã nhân viên, họ tên, ngày sinh, email, địa chỉ, số điện thoại, số ngày công làm việc trong tháng, lương ngày, lương thực nhận.

## Cấu trúc dữ liệu ```nhanVien```
 ```
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
 ```

## Luồng nhập dữ liệu
1. Nhập mã nhân viên
2. Nhập họ tên
3. Nhập ngày sinh
4. Nhập email
5. Nhập địa chỉ
6. Nhập số điện thoại
7. Nhập số ngày công làm việc trong tháng
8. Nhập lương ngày
9. Tính lương thực nhận theo công thức: ```luongThucNhan = soNgayCong * luongNgay```
10. Lặp lại bước 1 cho đến khi hết dữ liệu
