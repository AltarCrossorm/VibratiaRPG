#pragma once
/**
 * @file fights.hpp
 * @date 2026/08/12
 * @authors
 *      - 
 * @brief 
 *
 * @ai
 *
 * Comments and Documentation are here to help the developers who come after.
 */
#include "_base.hpp"

struct Fights final : public ORM_BASE
{
	time_t startFight;
	long channelID;
	bool isPvP;
	long opponent1;
	long opponent2;
	bool isEnded;

	DECLARE_ORM_METADATA(Fights, id, startFight, channelID, isPvP, opponent1, opponent2, isEnded)
};

class FightsRepository final : public Repository<Fights>
{
public:
	virtual std::string getTableName() override {
		return "fights";
	}

	virtual Fights buildObject(std::vector<RowValue> val) override {
		BUILD_OBJECT_START(Fights,val)
		BUILD_OBJECT_ADD_FIELD_WITH_INT_CAST(startFight,time_t)
		BUILD_OBJECT_ADD_FIELD(channelID,long)
		BUILD_OBJECT_ADD_FIELD_WITH_INT_CAST(isPvP,bool)
		BUILD_OBJECT_ADD_FIELD(opponent1,long)
		BUILD_OBJECT_ADD_FIELD(opponent2,long)
		BUILD_OBJECT_ADD_FIELD_WITH_INT_CAST(isEnded,bool)
		BUILD_OBJECT_END
	}

	std::optional<Fights> getLastFightFromPosition(long position) {
		std::string fightsQuery = R"(
			select
				*
			from
				fights f
			where
				f.channelID = ?
			order by
				startFight DESC
			;)";
		auto lastFight = SQLite3::Connection::inst()->cursor().execute(fightsQuery,position)->fetchone();
		if(lastFight.empty())
			return std::nullopt;
		else
			return std::make_optional<Fights>(this->buildObject(lastFight));
	}
};
