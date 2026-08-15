#pragma once
/**
 * @file _base.hpp
 * @date 2026/08/09
 * @authors
 *      - 
 * @brief 
 *
 * @ai
 *
 * Comments and Documentation are here to help the developers who come after.
 */

#include "sqlite3.hpp"
#include <map>
#include <optional>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>
#include <tuple>
#include "_base_macros.hpp"

#define BUILD_OBJECT_ADD_FIELD(fieldname, type) obj.fieldname = GET_SQLITE3_VALUE<type>(BuildObjectVariant[inc]); inc++;
#define BUILD_OBJECT_ADD_FIELD_WITH_INT_CAST(fieldname,castType) obj.fieldname = static_cast<castType>(GET_SQLITE3_VALUE<long>(BuildObjectVariant[inc])); inc++;
#define BUILD_OBJECT_ADD_FIELD_WITH_FLOAT_CAST(fieldname,castType) obj.fieldname = static_cast<castType>(GET_SQLITE3_VALUE<double>(BuildObjectVariant[inc])); inc++;

#define BUILD_OBJECT_ADD_FIELD_OPTIONAL(fieldname, type) obj.fieldname = BuildObjectVariant[inc].index() == 0 ? std::nullopt : std::make_optional<type>(GET_SQLITE3_VALUE<type>(BuildObjectVariant[inc])); inc++;
#define BUILD_OBJECT_ADD_FIELD_OPTIONAL_WITH_INT_CAST(fieldname, castType) obj.fieldname = BuildObjectVariant[inc].index() == 0 ? std::nullopt : std::make_optional<castType>(static_cast<castType>(GET_SQLITE3_VALUE<long>(BuildObjectVariant[inc]))); inc++;
#define BUILD_OBJECT_ADD_FIELD_OPTIONAL_WITH_FLOAT_CAST(fieldname, castType) obj.fieldname = BuildObjectVariant[inc].index() == 0 ? std::nullopt : std::make_optional<castType>(static_cast<castType>(GET_SQLITE3_VALUE<double>(BuildObjectVariant[inc]))); inc++;

#define BUILD_OBJECT_START(type,variant) type obj; int inc = 0; auto BuildObjectVariant = variant; BUILD_OBJECT_ADD_FIELD_OPTIONAL(id,long)
#define BUILD_OBJECT_END return obj;

struct ORM_BASE
{
	std::optional<long> id = std::nullopt;

	static constexpr auto members() {
		return std::make_tuple(&ORM_BASE::id);
	}
};

using FieldValue = std::variant<std::monostate, long, double, std::string, bool>;
using Criteria = std::map<std::string, FieldValue>;

template<typename orm_obj>
requires std::is_base_of_v<ORM_BASE, orm_obj>
class Repository
{
public:
	~Repository() = default;

	virtual std::string getTableName() = 0;
	virtual orm_obj buildObject(std::vector<RowValue>) = 0;

	template<typename MemberType, typename ClassType>
    std::string getColumnName(MemberType ClassType::* member) const {
        // On délègue à une méthode static du type OrmObj ou de la classe fille
        return orm_obj::getColumnName(member);
    }
protected:
	orm_obj buildByID(std::vector<RowValue> val) {
		std::optional<orm_obj> optVal = this->findById(GET_SQLITE3_VALUE<long>(val[0]));
		if(optVal) {
			return optVal.value();
		} else {
			throw std::runtime_error("Objet non disponible malgré une trouvaille faite !");
		}
	}

	std::vector<orm_obj> buildByID(std::vector<Row> q) {
		std::vector<orm_obj> retVec;
		for	(auto &val : q) 
			retVec.push_back(this->buildByID(val));

		return retVec;
	}
public:

	std::optional<orm_obj> findById(long id) {
		auto res = SQLite3::Connection::inst()->cursor().execute("select * from "+this->getTableName()+" where id = ? ;", id)->fetchone();
		if (res.empty())
			return std::nullopt;
		else
			return std::make_optional<orm_obj>(this->buildObject(res));
	}

	std::vector<orm_obj> findAll(void) {
		auto list = SQLite3::Connection::inst()->cursor().execute("select * from "+this->getTableName()+";")->fetchall();
		std::vector<orm_obj> ret;
		for (auto &&result : list)
		{
			ret.push_back(this->buildObject(result));
		}
		return ret;
	}

	void add(orm_obj& obj) {
        // 1. Extraire les membres de l'objet
        constexpr auto mems = orm_obj::members();
        [[maybe_unused]] constexpr std::size_t numFields = std::tuple_size_v<decltype(mems)>;

        // 2. Construire la clause INSERT INTO table (col1, col2, ...) VALUES (?, ?, ...)
        std::string columns = "";
        std::string placeholders = "";

        std::apply([this, &columns, &placeholders](auto&&... refs) {
            std::size_t i = 0;
            ((
                columns += (i > 0 ? ", " : "") + this->getColumnName(refs),
                placeholders += (i > 0 ? ", ?" : "?"),
                ++i
            ), ...);
        }, mems);

        std::string query = "INSERT INTO " + getTableName() + " (" + columns + ") VALUES (" + placeholders + ");";

        // 3. Récupérer les valeurs de l'instance 'obj' pour chaque membre
        auto extractValues = [&obj, &query](auto&&... refs) {
            // obj.*refs permet d'éclater l'objet et d'accéder à obj.id, obj.ennemy_id, etc.
            SQLite3::Connection::inst()->cursor().execute(query, (obj.*refs)...);
        };

        std::apply(extractValues, mems);

		if (obj.id) {
			obj.id = std::make_optional<long>(SQLite3::Connection::inst()->last_insert_rowid());
		}
    }

	void removeById(long id) {
		SQLite3::Connection::inst()->cursor().execute("delete from "+this->getTableName()+" where id = ?;", id);
	}

	template<typename ...Args>
	requires (sizeof...(Args) % 2 == 0)
	std::vector<orm_obj> findBy(Args&&... args) {
		// static_assert(sizeof...(Args) % 2 == 0, 
        //     "findBy exige un nombre pair d'arguments : paires (Membre, Valeur) !");
		
		std::string sqlWhere = "";
        
        // On traite les arguments par paires grâce à une fonction helper
        processPairs(sqlWhere, std::forward<Args>(args)...);

        std::string query = "SELECT id FROM " + getTableName();
        if (!sqlWhere.empty()) {
            query += " WHERE " + sqlWhere;
        }

        auto q = SQLite3::Connection::inst()->cursor().execute(query)->fetchall();
        return this->buildByID(q);
	}

	template<typename MemberPtr, typename Value, typename... Rest>
    void processPairs(std::string& sqlWhere, MemberPtr member, Value&& value, Rest&&... rest) {
		if(!sqlWhere.empty()) sqlWhere += " and ";

		sqlWhere += getColumnName(member) + " = ";

		if constexpr (std::is_same_v<std::decay_t<Value>, std::string> || 
                      std::is_same_v<std::decay_t<Value>, const char*>) {
            sqlWhere += "'" + std::string(value) + "'";
        } else if constexpr (std::is_same_v<std::decay_t<Value>, bool>) {
            sqlWhere += value ? "1" : "0";
        } else {
            sqlWhere += std::to_string(value);
        }

        if constexpr (sizeof...(Rest) > 0) {
            processPairs(sqlWhere, std::forward<Rest>(rest)...);
        }

	}

	std::vector<orm_obj> findBy(const Criteria& criteria) {
        std::string query = "SELECT id FROM " + getTableName() + " WHERE ";
        
        bool first = true;
        for (const auto& [column, value] : criteria) {
            if (!first) query += " AND ";
            query += column + " = ";
            
            std::visit([&query](auto&& arg) {
                using ValueType = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<ValueType, std::string> || std::is_same_v<ValueType, const char*>) {
                    query += "'" + arg + "'"; // Ajout des guillemets pour le SQL
                } else if constexpr (std::is_same_v<ValueType, bool>) {
                    query += arg ? "1" : "0";
				} else if constexpr (std::is_same_v<ValueType, std::monostate>) {
					query += "null";
                } else {
                    query += std::to_string(arg);
                }
            }, value);

            first = false;
        }

        auto q = SQLite3::Connection::inst()->cursor().execute(query)->fetchall();
        return this->buildByID(q);
    }
};
