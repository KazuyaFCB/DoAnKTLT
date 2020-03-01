//LEVEL 3: TÍNH TOÁN CÁC BIỂU THỨC VỚI SỐ NGUYÊN CỰC LỚN ĐƯỢC LƯU SẴN TRONG FILE
//Lưu ý: Chỉ thực hiện được những phép tính có cú pháp đúng. Ví dụ: 2 + * 3 sẽ không tính được.
//Phép chia không hết sẽ lấy phần nguyên
//Phép chia không có nghĩa ví dụ : 1/0 sẽ không tính được

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct BigNum {
	char chuso[500];
	int len;
};

const int MAX = 500;

BigNum Tong(BigNum a, BigNum b);
BigNum Hieu(BigNum a, BigNum b);
BigNum Tich(BigNum x, BigNum y);
BigNum Thuong(BigNum a, BigNum b);
int SoSanh(BigNum a, BigNum b);
char* TinhBieuThuc(char str[], int len);
void DocGhiFile();

BigNum Tong(BigNum a, BigNum b)
{
	char t;
	BigNum result,result2;
	int i, j, tempt;
	bool carry = 0;
	//result.chuso = (char*)malloc((a.len + 2)*sizeof(char));
	if (a.chuso[0] == '-' && b.chuso[0] != '-')
	{
		a.chuso[0] = '0';
		return Hieu(b, a);
	}
	else if (a.chuso[0] != '-' && b.chuso[0] == '-')
	{
		b.chuso[0] = '0';
		return Hieu(a, b);
	}
	else if (a.chuso[0] == '-' && b.chuso[0] == '-')
	{
		a.chuso[0] = b.chuso[0] = '0';
		strcpy(result.chuso, "-");
		result2 = Tong(a, b);
		strcat(result.chuso, result2.chuso);
		result.len = result2.len + 1;
		return result;
	}
	if (a.len < b.len)
	{
		result2 = Tong(b, a);
		strcpy(result.chuso, result2.chuso);
		result.len = result2.len;
		return result;
	}
	for (i = 0; i < b.len; i++)
	{
		tempt = a.chuso[a.len - i - 1] - '0' + b.chuso[b.len - i - 1] - '0' + carry;
		carry = 0;
		if (tempt < 10)
			result.chuso[i] = tempt + '0';
		else
		{
			result.chuso[i] = tempt - 10 + '0';
			carry = 1;
		}
	}
	for (; i < a.len; i++)
	{
		tempt = a.chuso[a.len - i - 1] - '0' + carry;
		carry = 0;
		if (tempt < 10)
			result.chuso[i] = tempt + '0';
		else
		{
			result.chuso[i] = tempt - 10 + '0';
			carry = 1;
		}
	}
	if (carry)
	{
		result.chuso[i] = '1';
		i++;
	}
	//Xóa số 0 ở đầu (Ví dụ 00001234 thì cũng giống 1234), lúc này số 0 ở cuối
	for (; result.chuso[i - 1] == '0' && i - 1 > 0; i--)
		result.chuso[i - 1] = '\0';
	//Đảo chuỗi
	for (j = 0; j < i / 2; j++)
	{
		t = result.chuso[j];
		result.chuso[j] = result.chuso[i - 1 - j];
		result.chuso[i - 1 - j] = t;
	}
	result.chuso[i] = '\0';
	result.len = i;
	return result;
}

BigNum Hieu(BigNum a, BigNum b)  //Hàm chỉ xử lý cho số nguyên dương và a > b
{
	char t;
	BigNum result, result2;
	int i, j, tempt, real_len_a, real_len_b, So_0_Dau_a, So_0_Dau_b;  //real là độ dài thực sự (không tính những chữ số 0 ở đầu)
	bool carry = 0;
	if (a.chuso[0] == '-' && b.chuso[0] != '-')
	{
		a.chuso[0] = '0';
		strcpy(result.chuso, "-");
		result2 = Tong(a, b);
		strcat(result.chuso, result2.chuso);
		result.len = result2.len + 1;
		return result;
	}
	else if (a.chuso[0] != '-' && b.chuso[0] == '-')
	{
		b.chuso[0] = '0';
		return Tong(a, b);
	}
	else if (a.chuso[0] == '-' && b.chuso[0] == '-')
	{
		a.chuso[0] = b.chuso[0] = '0';
		return Hieu(b, a);
	}
	//i, j là chữ số KHÁC 0 đầu tiên của a, b
	i = 0;
	while (a.chuso[i] == '0' && a.chuso[i + 1] != '\0')
		i++;
	j = 0;
	while (b.chuso[j] == '0' && b.chuso[j + 1] != '\0')
		j++;
	//a=0, b!=0
	if (a.chuso[i] == '0' && b.chuso[j] != '0')
	{
		strcpy(result.chuso, "-");
		strcat(result.chuso, b.chuso);
		result.len = b.len + 1;
		return result;
	}
	//a!=0, b=0
	else if (a.chuso[i] != '0' && b.chuso[j] == '0')
		return a;
	else if (a.chuso[i] == '0' && b.chuso[j] == '0')
	{
		strcpy(result.chuso, "0");
		result.len = 1;
		return result;
	}
	//Khi tới đây được thì a, b đảm bảo dương
	//VD: a = 1234 , b = 567890 thì khi so sánh, a sẽ bắt đầu từ 1 và b sẽ bắt đầu từ 7
	real_len_a = a.len - i;    //i, j là số chữ số 0 ở đầu
	real_len_b = b.len - j;
	So_0_Dau_a = i;
	So_0_Dau_b = j;
	if (real_len_a < real_len_b)   //Độ dài chuỗi không tính những số 0 ở đầu
	{
		strcpy(result.chuso, "-");
		result2 = Hieu(b, a);
		strcat(result.chuso, result2.chuso);
		result.len = result2.len + 1;
		return result;
	}
	else if (real_len_a == real_len_b)
	{
		for (; i < a.len; i++, j++)
		{
			if (int(a.chuso[i] - '0') < int(b.chuso[j] - '0'))
			{
				strcpy(result.chuso, "-");
				result2 = Hieu(b, a);
				strcat(result.chuso, result2.chuso);
				result.len = result2.len + 1;
				return result;
			}
			else if (int(a.chuso[i] - '0') > int(b.chuso[j] - '0'))
				break;
		}
		if (i == a.len)
		{
			strcpy(result.chuso, "0");
			result.len = 1;
			return result;
		}
	}
	for (i = 0; i < real_len_b; i++)
	{
		tempt = int(a.chuso[a.len - i - 1] - '0') - int(b.chuso[b.len - i - 1] - '0') - carry;
		carry = 0;
		if (tempt < 0)
		{
			tempt += 10;
			carry = 1;
		}
		result.chuso[i] = tempt + '0';
	}
	for (; i < real_len_a; i++)
	{
		tempt = int(a.chuso[a.len - i - 1] - '0') - carry;
		carry = 0;
		if (tempt < 0)
		{
			tempt += 10;
			carry = 1;
		}
		result.chuso[i] = tempt + '0';
	}
	//Xóa số 0 cuối result
	for (; result.chuso[i - 1] == '0'; i--)
		result.chuso[i - 1] = '\0';
	//Đảo chuỗi result
	for (j = 0; j < i / 2; j++)
	{
		t = result.chuso[j];
		result.chuso[j] = result.chuso[i - 1 - j];
		result.chuso[i - 1 - j] = t;
	}
	result.chuso[i] = '\0';
	result.len = i;
	return result;
}

BigNum Tich(BigNum x, BigNum y) //x*y = (10^n * a + b)*(10^n * c+ d) = 10^(2n)*a*c + 10^n *(a*d+b*c) + b*d = 10^(2n)*a*c + 10^n * (a-b)*(d-c) + b*d + 10^n *(a*c+b*d)
{
	BigNum a, b, c, d, tich1, tich2, tich3, result, result2;
	int i, j, n, So0Cuoi = 0, max;
	max = (x.len + y.len + abs(x.len - y.len)) / 2;
	if (x.len < 5 && y.len < 5)
	{
		i = (atoi(x.chuso))*(atoi(y.chuso));
		_itoa(i, result.chuso, 10);
		result.len = strlen(result.chuso);
		return result;
	}
	if ((x.chuso[0] == '-' && y.chuso[0] != '-'))
	{
		strcpy(result.chuso, "-");
		x.chuso[0] = '0';
		result2 = Tich(x, y);
		strcat(result.chuso, result2.chuso);
		result.len = result2.len + 1;
		return result;
	}
	else if ((x.chuso[0] != '-' && y.chuso[0] == '-'))
	{
		strcpy(result.chuso, "-");
		y.chuso[0] = '0';
		result2 = Tich(x, y);
		strcat(result.chuso, result2.chuso);
		result.len = result2.len + 1;
		return result;
	}
	else if (x.chuso[0] == '-' && y.chuso[0] == '-')
	{
		x.chuso[0] = y.chuso[0] = '0';
		return Tich(x, y);
	}
	//Duyệt để đảm bảo không có thừa số nào bằng = 0. Vì nếu có thừa số bằng 0 (VD: 1234*00000000, làm vậy thì ta sẽ cân bằng thành 12340000*00000000=0, lát nữa chia 10000 (xóa 4 số 0 ở cuối) sẽ không còn gì -> Lỗi
	//Xuống được dưới đây tức là không thể có TH âm (vì đã xét âm ở trên) nên chỉ có thể 0*a, a*0, 0*0
	for (i = 0; i < x.len && x.chuso[i] == '0'; i++);
	if (i == x.len)
	{
		strcpy(result.chuso, "0");
		result.len = 1;
		return result;
	}
	for (i = 0; i < y.len && y.chuso[i] == '0'; i++);
	if (i == y.len)
	{
		strcpy(result.chuso, "0");
		result.len = 1;
		return result;
	}
	//Thêm số 0 ở cuối cho những số nhỏ hơn để cân bằng số chữ số của 2 thừa số
	if (x.len > y.len)
	{
		while (x.len > y.len)
		{
			y.chuso[y.len] = '0';
			y.len++;
			So0Cuoi++;
		}
		y.chuso[y.len] = '\0';
	}
	else if (x.len < y.len)
	{
		while (x.len < y.len)
		{
			x.chuso[x.len] = '0';
			x.len++;
			So0Cuoi++;
		}
		x.chuso[x.len] = '\0';
	}
	n = x.len;
	//Tính a,b,c,d
	for (i = 0; i < n - n / 2; i++)
	{
		a.chuso[i] = x.chuso[i];
		c.chuso[i] = y.chuso[i];
	}
	a.chuso[i] = c.chuso[i] = '\0';
	a.len = c.len = i;
	for (j = 0; i < n; i++, j++)
	{
		b.chuso[j] = x.chuso[i];
		d.chuso[j] = y.chuso[i];
	}
	b.chuso[j] = d.chuso[j] = '\0';
	b.len = d.len = j;
	result2 = Tich(a, c);
	strcpy(tich1.chuso, result2.chuso);                    //ac
	tich1.len = result2.len;
	result2 = Tich(Hieu(a, b), Hieu(d, c));
	strcpy(tich2.chuso, result2.chuso);               //(a-b)*(d-c)
	tich2.len = result2.len;
	result2 = Tich(b, d);
	strcpy(tich3.chuso, result2.chuso);                    //bd
	tich3.len = result2.len;
	//Tính 10^(n/2) * (a*c+b*d)
	result = Tong(tich1, tich3);
	for (i = 0; i < n / 2; i++, result.len++)
		result.chuso[result.len] = '0';
	result.chuso[result.len] = '\0';
	result = Tong(result, tich3);             //b*d + 10^(n/2) *(a*c+b*d)
	//Tính (10^n)*a*c
	for (j = 0; j < n - n % 2; tich1.len++, j++)
		tich1.chuso[tich1.len] = '0';
	tich1.chuso[tich1.len] = '\0';
	//Tính 10^(n/2) * (a-b)(d-c)
	for (j = 0; j < n / 2; tich2.len++, j++)
	{
		tich2.chuso[tich2.len] = '0';
	}
	tich2.chuso[tich2.len] = '\0';
	result = Tong(result, tich2);
	result = Tong(result, tich1);
	
	while (So0Cuoi > 0)
	{
		result.chuso[result.len - 1] = '\0';
		result.len--;
		So0Cuoi--;
	}
	return result;
}

int SoSanh(BigNum a, BigNum b)
{
	int i = 0, j = 0, p = 1;
	if (a.chuso[0] == '-')
		i = 1;
	if (b.chuso[0] == '-')
		j = 1;
	//Tìm chữ số KHÁC 0 đầu tiên
	for (; i < a.len && a.chuso[i] == '0'; i++);
	for (; j < b.len && b.chuso[j] == '0'; j++);
	//(a==0 && b<0) || (a>0 && (b==0 || b<0)
	if ((i == a.len && b.chuso[0] == '-' && j < b.len) || (a.chuso[0] != '-' && i < a.len && (j == b.len || (b.chuso[0] == '-' && j < b.len))))
		return 1;
	//a==b==0
	if (i == a.len && j == b.len)
		return 0;
	//(a==0 && b>0) || (a<0 && (b==0 || b>0))
	if ((i == a.len && b.chuso[0] != '-' && j < b.len) || (a.chuso[0] == '-' && i < a.len && (j == b.len || (b.chuso[0] != '-' && j < b.len))))
		return -1;
	//TH cùng dấu
	if (a.chuso[0] == '-')
		p = -1;
	if (a.len - i > b.len - j) //a nhiều chữ số #0 hơn b
		return p;
	if (a.len - i < b.len - j) //a ít chữ số #0 hơn b
		return -p;
	for (; i < a.len && a.chuso[i] == b.chuso[j]; i++, j++);
	if (i == a.len)
		return 0;
	if (a.chuso[i] > b.chuso[j])
		return p;
	if (a.chuso[i] < b.chuso[j])
		return -p;
}

BigNum Thuong(BigNum a, BigNum b)     //Chỉ áp dụng cho phép chia hết và phép chia có nghĩa
{
	int i, rest = 0, dem0;
	BigNum result, result2, tempt, chusocuathuong;
	if (a.chuso[0] == '-' && b.chuso[0] != '-')
	{
		strcpy(result.chuso, "-");
		a.chuso[0] = '0';
		result2 = Thuong(a, b);
		strcat(result.chuso, result2.chuso);
		result.len = result2.len + 1;
		return result;
	}
	else if (a.chuso[0] != '-' && b.chuso[0] == '-')
	{
		strcpy(result.chuso, "-");
		b.chuso[0] = '0';
		result2 = Thuong(a, b);
		strcat(result.chuso, result2.chuso);
		result.len = result2.len + 1;
		return result;
	}
	else if (a.chuso[0] == '-' && b.chuso[0] == '-')
	{
		a.chuso[0] = b.chuso[0] = '0';
		return Thuong(a, b);
	}
	if (SoSanh(a, b) < 0)
	{
		strcpy(result.chuso, "0");
		result.len = 1;
		return result;
	}
	dem0 = 0;
	//Xóa những số 0 ở đầu của a và b (nếu có)
	while (a.chuso[dem0] == '0' && dem0 < a.len - 1)
		dem0++;
	if (dem0 > 0)
	{
		a.len = a.len - dem0;
		for (i = 0; i < a.len; i++)
			a.chuso[i] = a.chuso[i + dem0];
		a.chuso[i] = '\0';
	}
	dem0 = 0;
	while (b.chuso[dem0] == '0' && dem0 < b.len - 1)
		dem0++;
	if (dem0 > 0)
	{
		b.len = b.len - dem0;
		for (i = 0; i < b.len; i++)
			b.chuso[i] = b.chuso[i + dem0];
		b.chuso[i] = '\0';
	}
	strncpy(tempt.chuso, a.chuso, b.len*sizeof(char));
	tempt.chuso[b.len] = '\0';
	tempt.len = b.len;
	if (SoSanh(tempt, b) < 0)
	{
		tempt.chuso[b.len] = a.chuso[b.len];
		tempt.chuso[b.len + 1] = '\0';
		tempt.len++;
		rest++;
	}
	result.len = 0;
	while (rest <= a.len - b.len)
	{
		for (i = 1; i <= 10; i++)
		{
			_itoa(i, chusocuathuong.chuso, 10);
			chusocuathuong.len = 1 + i / 10;
			if (SoSanh(tempt, Tich(b, chusocuathuong)) == -1)
			{
				i--;
				_itoa(i, chusocuathuong.chuso, 10);
				chusocuathuong.len = 1;
				result.chuso[result.len] = chusocuathuong.chuso[0];
				result.chuso[result.len + 1] = '\0';
				result.len++;
				break;
			}
		}
		tempt = Hieu(tempt, Tich(b, chusocuathuong));
		rest++;
		tempt.chuso[tempt.len] = a.chuso[b.len - 1 + rest];
		tempt.len++;
		tempt.chuso[tempt.len] = '\0';
	}
	i = 0; dem0 = 0;
	return result;
}

char* TinhBieuThuc(char str[], int len)
{
	char queue[MAX][MAX], stack[MAX][MAX], numbertempt[MAX], temptstr[MAX], *result;
	BigNum calcstack[MAX], t;
	int sptqueue = 0, sptstack = 0, sptnumbertempt = 0, sptcalcstack = 0, sokitu[MAX], i, dem0; float tempt;
	result = (char*)malloc(MAX * sizeof(char));
	for (int i = 0; i < len; i++)
	{
		///Gặp số thì push vào queue
		if ((str[i] >= '0' && str[i] <= '9') || (str[i] == '-' && (i == 0 || str[i - 1] == '(' || str[i - 1] == '+' || str[i - 1] == '-' || str[i - 1] == '*' || str[i - 1] == '/')))
		{
			numbertempt[sptnumbertempt] = str[i];
			sptnumbertempt++;
			i++;
			while ((str[i] >= '0' && str[i] <= '9') && i < len)
			{
				numbertempt[sptnumbertempt] = str[i];
				sptnumbertempt++;
				i++;
			}
			numbertempt[sptnumbertempt] = '\0';
			sokitu[sptqueue] = sptnumbertempt;
			strcpy(queue[sptqueue], numbertempt);
			sptqueue++;
			i--;
			sptnumbertempt = 0;
		}
		//Kiểm tra đầu stack xem có ưu tiên hơn hay không, nếu ưu tiên thì pull toán tử đầu stack và push toán tử đó vào cuối queue
		//Làm vậy cho đến khi hết stack hoặc gặp dấu "(" hoặc gặp toán tử ưu tiên thấp hơn thì break
		else if (str[i] == '+' || str[i] == '-')
		{
			if (sptstack == 0)
			{
				stack[sptstack][0] = str[i];
				stack[sptstack][1] = '\0';
				sptstack++;
			}
			else
			{
				while (stack[sptstack - 1][0] == '+' || stack[sptstack - 1][0] == '-' || stack[sptstack - 1][0] == '*' || stack[sptstack - 1][0] == '/')
				{
					queue[sptqueue][0] = stack[sptstack - 1][0];
					queue[sptqueue][1] = '\0';
					sptqueue++;
					sptstack--;
				}
				stack[sptstack][0] = str[i];
				sptstack++;
			}
		}
		else if (str[i] == '*' || str[i] == '/')
		{
			while (stack[sptstack - 1][0] == '*' || stack[sptstack - 1][0] == '/')
			{
				queue[sptqueue][0] = stack[sptstack - 1][0];
				queue[sptqueue][1] = '\0';
				sptqueue++;
				sptstack--;
			}
			stack[sptstack][0] = str[i];
			sptstack++;
		}
		//Gặp "(" thì push vào stack
		else if (str[i] == '(')
		{
			stack[sptstack][0] = str[i];
			stack[sptstack][1] = '\0';
			sptstack++;
		}
		//Gặp ")" thì pull tất cả các toán tử trong stack và push các toán tử đó vào queue cho đến khi gặp dấu "("
		else if (str[i] == ')')
		{
			while (stack[sptstack - 1][0] != '(')
			{
				queue[sptqueue][0] = stack[sptstack - 1][0];
				queue[sptqueue][1] = '\0';
				sptqueue++;
				sptstack--;
			}
			sptstack--;  //Bỏ dấu "("
		}
	}
	//Khi duyệt hết biểu thức ban đầu, kiểm tra trong stack còn toán tử nào không, nếu còn thì pull hết và push vào queue
	while (sptstack > 0)
	{
		queue[sptqueue][0] = stack[sptstack - 1][0];
		queue[sptqueue][1] = '\0';
		sptqueue++;
		sptstack--;
	}
	for (int i = 0; i < sptqueue; i++)
	{
		if (queue[i][0] >= '0' && queue[i][0] <= '9' || (queue[i][0] == '-' && queue[i][1] >= '0' && queue[i][1] <= '9'))
		{
			strcpy(calcstack[sptcalcstack].chuso, queue[i]);
			calcstack[sptcalcstack].len = sokitu[i];
			sptcalcstack++;
		}
		else if (queue[i][0] == '+')
		{
			t = Tong(calcstack[sptcalcstack - 2], calcstack[sptcalcstack - 1]);
			calcstack[sptcalcstack - 2] = t;
			sptcalcstack--;
		}
		else if (queue[i][0] == '-')
		{
			t = Hieu(calcstack[sptcalcstack - 2], calcstack[sptcalcstack - 1]);
			calcstack[sptcalcstack - 2] = t;
			sptcalcstack--;
		}
		else if (queue[i][0] == '*')
		{
			t = Tich(calcstack[sptcalcstack - 2], calcstack[sptcalcstack - 1]);
			calcstack[sptcalcstack - 2] = t;
			sptcalcstack--;
		}

		else if (queue[i][0] == '/')
		{
			t = Thuong(calcstack[sptcalcstack - 2], calcstack[sptcalcstack - 1]);
			calcstack[sptcalcstack - 2] = t;
			sptcalcstack--;
		}
	}
	//Xóa những số 0 ở đầu của kết quả sau cùng
	i = 0;
	dem0 = 0;
	if (calcstack[0].chuso[0] == '-')
		i = 1;
	for (; calcstack[0].chuso[i] == '0' && i - 1 < calcstack[0].len; i++, dem0++);
	calcstack[0].len = calcstack[0].len - dem0;
	i = 0;
	if (calcstack[0].chuso[0] == '-')
		i = 1;
	while (i < calcstack[0].len)
	{
		calcstack[0].chuso[i] = calcstack[0].chuso[i + dem0];
		i++;
	}
	calcstack[0].chuso[i] = '\0';
	strcpy(result, calcstack[0].chuso);
	return result;
}

void DocGhiFile()
{
	FILE *fpin, *fpout;
	char str[2000], ch, *result;
	int len = 0;
	fpin = fopen("BieuThuc.txt", "r");
	fpout = fopen("KetQua.txt", "w+");
	while (1)
	{
		ch = fgetc(fpin);
		str[len] = ch;
		len++;
		if (ch == EOF || ch == '\n')
		{
			len--;
			str[len] = '\0';
			result = TinhBieuThuc(str, len);
			fprintf(fpout, "%s\n", result);
			free(result);
			len = 0;
			if (ch == EOF)
			{
				fclose(fpin);
				fclose(fpout);
				break;
			}
		}
	}
}

void main()
{
	DocGhiFile();
	system("pause");
}