# hashtable

[![GitHub license](https://img.shields.io/github/license/mashape/apistatus.svg?style=flat-square)](http://goldsborough.mit-license.org)

`hashtable` is a feature-complete, generic and customizable separate-chaining hashtable in pure C.

## Usage

```C
#include "hashtable.h"

int main(int argc, const char* argv[]) {
	HashTable table;

	/* Choose initial capacity of 10 */
	/* Specify the size of the keys and values you want to store once */
	ht_setup(&table, sizeof(int), sizeof(double), 10);

	ht_reserve(&table, 100);

	int x = 6;
	double y = 9;
	ht_insert(&table, &x, &y);

	if (ht_contains(&table, &x)) {
		y = *(double*)ht_lookup(&table, &x);
		/* Or use convenience macros */
		y = HT_LOOKUP_AS(double, &table, &x);
		printf("%d's value is: %f\n", x, y);
	}

	ht_erase(&table, &x);

	ht_clear(&table);
	ht_destroy(&table);
}
```

## License

This project is released under the [MIT License](http://goldsborough.mit-license.org). For more information, see the `LICENSE` file.

## Authors

[Peter Goldsborough](http://www.goldsborough.me) + [cat](https://goo.gl/IpUmJn) :heart:

<a href="https://gratipay.com/~goldsborough/"><img src="http://img.shields.io/gratipay/goldsborough.png?style=flat-square"></a>
