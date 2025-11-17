# IT3323_week1

## Chương trình: Tạo chỉ mục từ file văn bản

Chương trình đọc một file văn bản, loại bỏ stop words, lập chỉ mục các từ xuất hiện, và xuất kết quả ra file `index.txt`.

---

## 1. Yêu cầu

* Có **gcc** để biên dịch chương trình C.
* Makefile để sử dụng `make`.
* File stop words: `stopw.txt`.
* File văn bản muốn lập chỉ mục (mặc định là `alice30.txt`).

---

## 2. Cấu trúc Makefile

```makefile
TEXTFILE ?= alice30.txt

all: run

run:
	gcc index.c -o index
	./index $(TEXTFILE)

clean:
	rm -f index
	rm -f index.txt
```

* `TEXTFILE`: Tên file văn bản đầu vào (mặc định `alice30.txt`).
* `all`: Biên dịch và chạy chương trình.
* `run`: Chỉ chạy chương trình với file được chỉ định.
* `clean`: Xóa file biên dịch và kết quả.

---

## 3. Cách chạy

### 3.1 Chạy với file mặc định

```bash
make
```

Hoặc

```bash
make run
```

> Chương trình sẽ đọc `alice30.txt` và xuất kết quả ra `index.txt`.

### 3.2 Chạy với file khác

```bash
make run TEXTFILE=mytext.txt
```

> Thay `mytext.txt` bằng tên file văn bản bạn muốn lập chỉ mục.

### 3.3 Xóa file biên dịch và kết quả

```bash
make clean
```

> Xóa file `index` và `index.txt`.

---

## 4. Kết quả

* Chương trình sẽ in ra màn hình danh sách các từ cùng các dòng xuất hiện.
* Đồng thời xuất ra file `index.txt`.

