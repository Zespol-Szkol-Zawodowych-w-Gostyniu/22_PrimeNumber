#include "bigint.h"

bigint::bigint() : err(0) {};
bigint::bigint(std::string num) {
	this->err = 0;
	this->len = 0;
	for (int i = 0; i < num.size(); i++)//sprawdzenie czy w ciagu s¹ tylko cyfry (ASCII)
		if (!((int(num[i]) > 47) && (int(num[i]) < 58))) {
			this->err = 1;
			break;
		}
	if (this->err == 0) {
		this->number = num;
		this->len = num.size();
	}
}
std::string bigint::getNumber() { return this->number; };
int bigint::getLen() {	return this->len; };
int bigint::bingetLen() { return this->binlen; }

void bigint::setNumber(std::string s) {
	this->number = s;
	this->len = s.size();
}

bigint bigint::operator +(const bigint& num) {
	bigint obj;
	std::string c = "";
	std::string a = this->number;
	std::string b = num.number;
	int da, db,x,r,q;
	da = a.size();
	db = b.size();
	if (da > db) {
		for (int i = 0; i <= (da - db); i++) b = "0" + b;
		a = "0" + a;//dodatkowe miejsce z przodu dla nadmiaru
		db = da;
	}
	else {
		for (int i = 0; i <= (db - da); i++) a = "0" + a;
		b = "0" + b;//dodatkowe miejsce z przodu dla nadmiaru
		da = db;
	}
	for (int i = 0; i <= da; i++) c += "0";
	//dodawanie w "s³upku" - zaczynam od koñca, od prawej strony
	for (int i = da; i >= 0; i--) {
		x = (int(a[i]) - 48) + (int(b[i]) - 48) + (int(c[i])-48);//w kodzie ASCII cyfra 0 ma kod 48, 1 -> kod 49 itd.
		if (x >= 10) {
			r = x % 10;
			c[i] = char(r + 48);
			//q = x / 10;
			//c[i - 1] = char(q + 48);
			c[i - 1] = '1';
		}
		else {
			c[i] = char(x + 48);
		}
	}
	if (c[0] == '0') {
		for (int i = 0; i < da; i++) c[i] = c[i + 1];
		c.pop_back();
	}
	obj.number = c;
	obj.len = c.size();
	return obj;
}

bigint bigint::operator -(const bigint& num) {
	bigint obj("0");
	std::string c = "";
	std::string a = this->number;
	std::string b = num.number;
	int da, db, x, j, y ,z;
	da = a.size();
	db = b.size();
	if (this->number == num.number) {
	
		return obj;
	}
	if (da < db) {
		c = "-1";
		obj.number = c;
		this->err = 2;
		return obj;
	}
	if (da == db) {
		if (a == b) {
			c = "0";
			obj.number = c;
			this->err = 0;
			return obj;
		}
		int i = 0;
		while ( (int(a[i]) <= int(b[i]) ) && i < da) {
			if (int(a[i]) < int(b[i])) {
				c = "-1";
				obj.number = c;
				this->err = 2;
				return obj;
			}
			i++;
		}
	}
	for (int i = 0; i < da; i++) c += "0"; //c=0000000...
	for (int i = 0; i < da - db; i++) b = "0" + b;
	for (int i = da - 1; i >= 0; i--) {
		if (int(a[i]) < int(b[i])) {//odjemna < odjemnik
			j = i - 1;//indeks s¹siada który nam pozyczy
			y = int(a[j]) - 48;//co ma s¹siad
			z = 0; //zliczanie s¹siadów;
			while (y == 0 && i > 0) {
				j--;
				z++;
				if (z > 0) a[j + 1] = char(57);//->9
				y = int(a[j]) - 48;
			}
			a[j] = char(int(a[j]) - 1);
			y = 10 + (int(a[i]) - 48);
			x = y - (int(b[i]) - 48);
		}
		else {
			x = (int(a[i]) - int(b[i]));//x = (int(a[i]) - 48) - (int(b[i]) - 48);
		}
		c[i] = char(x + 48);
	}
	j = 0;
	while (c[0] == '0') {
		for (int i = 0; i < da-j; i++) c[i] = c[i + 1];
		c.pop_back();
		j++;
	}

	obj.number = c;
	obj.len = c.size();
	return obj;
}

bigint bigint::operator *(const bigint& num) {
	bigint obj;
	std::string c = "";
	std::string a = this->number;
	std::string b = num.number;
	int da, db, x,r,q;
	da = a.size();
	db = b.size();
	if (this->number == "0" || num.number == "0") {
		obj.number = "0";
		obj.len = c.size();
		return obj;
	}
	if (da == 1 && db == 1) {
		int x = (int(a[0]) - 48) * (int(b[0]) - 48);
		if (x > 10) {
			/*
			 4
			*3
			--
            12 
			*/
			c = (char(x / 10) + 48);   //1         
			c += char(x % 10 + 48);    //12
		}
		else c = char(x) + 48;
		obj.number = c;
		this->err = 0;
		return obj;
	}
	if (da < db) {
		a = num.number;
		b = this->number;
		da = num.len;
		db = this->len;
	}
	/*
			  00923
			  00093
			-------
               2769
			  8297
		-----------
		      85739
	*/
	for (int i = 0; i < da; i++) b = "0" + b;
	for (int i = 0; i < db; i++) a = "0" + a;
	for (int i = 0; i < da + db; i++) c += "0";
	int i = db + da - 1; //tablica indeksowana od 0
	int di = 0;
	while (i >= da) {
		for (int j = db + da - 1; j >= db; j--) {
			x = (int(a[j]) - 48) * (int(b[i])- 48) + (int(c[j - di]) - 48);
			if (x >= 10) {
				r = x % 10;
				c[j - di] = char(r + 48);
				q = x / 10;
				c[j-di-1] = char(q + (int(c[j-di-1]) - 48) + 48);
			}
			else {
				c[j-di] = char(x + 48);
			}
		}
		i--;
		di++;
	}
	if (c[0] == '0') {
		for (int i = 0; i < da+db; i++) c[i] = c[i + 1];
		c.pop_back();
	}
	obj.number = c;
	obj.len = c.size();
	return obj;
}

bool bigint::operator <(const bigint& num) {
	std::string a = this->number;
	std::string b = num.number;
	int da, db;
	da = a.size();
	db = b.size();
	if (da > db) return false;
	if (db > da) return true;
	if (da == db) {
		if (a > b) return false;
		else if (a == b) return false;
			else return true;
	}
}

bool bigint::operator >(const bigint& num) {
	std::string a = this->number;
	std::string b = num.number;
	int da, db;
	da = a.size();
	db = b.size();
	if (da > db) return true;
	if (db > da) return false;
	if (da == db) {
		if (a > b) return true;
		else if (a == b) return false; 
		else return false;
	}
}

bool bigint::operator ==(bigint& num) {
	std::string num1 = this->number;
	std::string num2 = num.number;;
	if (num1 == num2) return true;
	else false;
}
bool bigint::operator !=(bigint& num) {
	std::string num1 = this->number;
	std::string num2 = num.number;
	if (num1 == num2) return false;
	else true;
}

bigint bigint::operator /(const bigint &num) {
	bigint obj("0");
	bigint r("0");
	bigint q("0");
	bigint w("0");
	std::string c = "", d="";
	std::string a = this->number;
	int i = 0;
	int da = a.size();
	int db = num.len;

	//szczegolny przypadek dla dzielnia przez 2
	if (num.number == "2") {
		/*
		69
		-----
		139:2
		12
		----
		19
		18
		---
		1
		*/
		int x = 0, y = 0;
		if (a == "1") {
			obj.number = "0";
			obj.len = 1;
			return obj;
		}
		while (i < da) {
			if (((int(a[i]) - 48) < 2) && i == 0) {
				x = ((int(a[i]) - 48) * 10 + (int(a[i + 1]) - 48)) / 2;
				y = ((int(a[i]) - 48) * 10 + (int(a[i + 1]) - 48)) % 2;
				c = c + char(x + 48);
				i++;
			}
			else {
				if (y != 0) x = (y * 10 + (int(a[i]) - 48)) / 2;
				else x = (int(a[i]) - 48) / 2;
				y = (int(a[i]) - 48) % 2;
				c = c + char(x + 48);
			}
			i++;
		}
		obj.number = c;
		obj.len = c.size();
		return obj;
	}
	//warunek brzegowy dla rekurencji -> dzielna < dzielnika
	obj.setNumber(this->number);
	if (obj<num) {
		obj.setNumber("0");
		return obj;
	}
	if ((da==db)|| (da-db==1)) {//je¿eli liczby s¹ zblizone co do wartoœci do siebie (ta sama d³ugoœæ lub +1) 
		int i = 0;
		while (!(obj<num)) {
			obj = obj - num;
			i++;
		}
		//czy jest równe
		if (obj.number == num.number) i++;
		obj.setNumber(std::to_string(i));
		return obj;
	}
	obj.setNumber("0");
	while (obj<num) {
		d = d + a[i];
		obj.setNumber(d);
		i++;
	}
	//klasyczne dzielenie na "kresce"
	while (i <= da) {
		r.setNumber(d);
		r = r / num;
		q.setNumber(d);
		//q = q % num;
		w = r * num;
		q = q - w;
		//-----------
		c = c + r.number;
		if (q.number == "0") d = "";  else d = q.number;
		d = d + a[i];
		i++;
		obj.setNumber(q.number);
	}
	obj.number = c;
	obj.len = c.size();
	return obj;
}

bigint bigint::operator %(const bigint& num) {
	bigint obj1("0");
	bigint obj2("0");
	bigint obj3("0");
	obj1 = this->number;
	obj2 = obj1 / num;
	obj3 = obj2 * num;
	obj2 = obj1 - obj3;
	obj2.len = obj2.number.size();
	return obj2;
}

void bigint::decTobin() {

	bigint obj("0");
	bigint c;
	std::string s = "";
	obj.number = this->number;
	bigint jeden("1");
	bigint dwa("2");
	int i = 0;
	while (obj > jeden) {
		c = obj % dwa;
		s = c.number+s;
		obj = obj / dwa;
		i++;
	}
	this->binnumber ="1"+s;
	this->binlen = this->binnumber.size();
}