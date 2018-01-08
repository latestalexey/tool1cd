#include "../catch.hpp"
#include <Parse_tree.h>
#include <Field.h>
#include <string>

static Field *load_field(const String &description)
{
	tree *field_tree = parse_1Ctext(description, "");
	tree *first_entry = field_tree->get_first()->get_first();
	bool has_version = false;
	Field *fld = Field::field_from_tree(first_entry, has_version, nullptr);
	delete field_tree;
	return fld;
}

TEST_CASE( "Проверка разбора полей", "[tool1cd][Fields]" ) {

	GIVEN ("Описание поля binary(16)") {
		String binary16 = "{\"_IDRREF\",\"B\",0,16,0,\"CS\"}";
		WHEN ("Парсим описание поля") {
			Field *fld = load_field(binary16);
			THEN("Имеем верно разобранное поле") {
				REQUIRE(fld->getname() == "_IDRREF");
				REQUIRE(fld->gettype() == type_fields::tf_binary);
				REQUIRE(fld->getlength() == 16);
				REQUIRE(fld->getlen() == 16);
				REQUIRE(fld->getnull_exists() == false);
			}
		}
	}

	GIVEN ("Описание поля nullable binary(40)") {
		String binary16 = "{\"_DATA\",\"B\",1,40,0,\"CS\"}";
		WHEN ("Парсим описание поля") {
			Field *fld = load_field(binary16);
			THEN("Имеем верно разобранное поле") {
				REQUIRE(fld->getname() == "_DATA");
				REQUIRE(fld->gettype() == type_fields::tf_binary);
				REQUIRE(fld->getlength() == 40);
				REQUIRE(fld->getlen() == 41);
				REQUIRE(fld->getnull_exists() == true);
			}
		}
	}

	GIVEN ("Описание поля version") {
		String version = "{\"_VERSION\",\"RV\",0,0,0,\"CS\"}";
		WHEN ("Парсим описание поля") {
			Field *fld = load_field(version);
			THEN("Имеем верно разобранное поле") {
				REQUIRE(fld->getname() == "_VERSION");
				REQUIRE(fld->gettype() == type_fields::tf_version);
				REQUIRE(fld->getnull_exists() == false);
			}
		}
	}
}

