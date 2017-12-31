//
// Created by Handa Wang on 9/24/17.
//

#ifndef JSON_JSON_H
#define JSON_JSON_H


#include <istream>
#include <map>

namespace toy {
	enum class JSONType {
		INT, DOUBLE, STRING, OBJECT, ARRAY, NUL
	};

	class JSON;

	namespace {
		class JSONImpl {
		public:
			JSONImpl() = default;

			~JSONImpl() = default;

			virtual JSONType type() const = 0;

			virtual JSONImpl *copy() const = 0;

			virtual std::string toString() const = 0;

			friend class JSONObjectImpl;

		protected:
			virtual void appendAsString(std::string &buffer) const = 0;
		};

		class JSONIntImpl : public JSONImpl {
		public:
			JSONIntImpl();

			explicit JSONIntImpl(int value);

			JSONType type() const override;

			JSONImpl *copy() const override;

			std::string toString() const override;

			friend class JSON;

		protected:
			void appendAsString(std::string &buffer) const override;

		private:
			int value_;
		};

		class JSONStringImpl : public JSONImpl {
		public:
			JSONStringImpl() = default;

			explicit JSONStringImpl(std::string value);

			JSONType type() const override;

			JSONImpl *copy() const override;

			std::string toString() const override;

		protected:
			void appendAsString(std::string &buffer) const override;

		private:
			std::string value_;
		};

		class JSONObjectImpl : public JSONImpl {
		public:
			JSONObjectImpl() = default;

			explicit JSONObjectImpl(const std::map<std::string, std::unique_ptr<JSON>> &value);

			explicit JSONObjectImpl(std::map<std::string, std::unique_ptr<JSON>> &&value);

			JSONType type() const override;

			JSONImpl *copy() const override;

			std::string toString() const override;

			std::map<std::string, std::unique_ptr<toy::JSON>> &map();

		protected:
			void appendAsString(std::string &buffer) const override;

		private:
			std::map<std::string, std::unique_ptr<toy::JSON>> value_;
		};
	}

	class JSON {
	public:
		JSON() = default;

		JSON(int value);

		JSON(std::string value);

		JSON(JSONType type);

		JSON(const JSON &other);

		JSON(JSON &&other) = default;

		JSON &operator=(const JSON &other);

		JSON &operator=(JSON &&other) = default;

		JSON &operator=(int value);

		JSON &operator=(std::string value);

		~JSON() = default;

		JSONType type() const;

		std::string toString();

		JSON &operator[](const std::string &key);

		friend class JSONObjectImpl;

	private:
		std::unique_ptr<JSONImpl> json_impl_;
	};

}


#endif //JSON_JSON_H
