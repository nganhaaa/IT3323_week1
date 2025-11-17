# IT3323_week1

## Chương trình: Tạo chỉ mục từ file văn bản

Chương trình đọc một file văn bản, loại bỏ stop words, lập chỉ mục các từ xuất hiện, và xuất kết quả ra file output.

**Định dạng xuất:**

```
từ <số_lần_xuất_hiện> <dòng1>, <dòng2>, ...
```

Ví dụ:

```
alice       5 1, 2, 3, 5, 10
```

---

## 1. Yêu cầu

* **gcc** để biên dịch chương trình C.
* File stop words: `stopw.txt`.
* File văn bản muốn lập chỉ mục.

---

## 2. Biên dịch và chạy

### Biên dịch thủ công

```bash
gcc index.c -o index
```

### Chạy chương trình

```bash
./index <file_van_ban> <file_output>
```

Ví dụ:

```bash
./index alice30.txt ketqua.txt
```

* `alice30.txt` → file văn bản đầu vào
* `ketqua.txt` → file xuất kết quả

Chương trình sẽ in ra màn hình và xuất ra file output.

---

## 3. Makefile

Makefile hỗ trợ biến:

```makefile
TEXTFILE ?= alice30.txt
OUTPUT ?= index.txt

all: run

run:
	gcc index.c -o index
	./index $(TEXTFILE) $(OUTPUT)

clean:
	rm -f index
	rm -f $(OUTPUT)
```

### Sử dụng Makefile

* Chạy với file mặc định:

```bash
make run
```

* Chạy với file khác:

```bash
make run TEXTFILE=mytext.txt OUTPUT=ketqua.txt
```

* Xóa file biên dịch và file output:

```bash
make clean
```

---

## 4. Kết quả

* File output có định dạng:

```
từ <số_lần_xuất_hiện> <dòng1>, <dòng2>, ...
```

* Đồng thời in ra màn hình với định dạng giống file output.
