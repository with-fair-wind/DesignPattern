#pragma once

#include <boost/algorithm/string/trim.hpp>
#include <boost/filesystem.hpp>

class Journal {
   public:
    explicit Journal(std::string title) : _title(std::move(title)) {}

    void add(const std::string& entry) {
        static int count = 1;
        const auto cleaned = boost::algorithm::trim_copy(entry);
        _entries.emplace_back(std::to_string(count++) + ": " + cleaned);
    }

    [[nodiscard]] const std::string& title() const { return _title; }
    [[nodiscard]] const std::vector<std::string>& entries() const { return _entries; }

   private:
    std::string _title;
    std::vector<std::string> _entries;
};

class PersistenceManager {
   public:
    static void save(const Journal& journal, const std::string& filename, bool overwrite = false) {
        if (overwrite || !boost::filesystem::exists(filename)) {
            std::ofstream ofs(filename);
            for (const auto& entry : journal.entries()) {
                ofs << entry << '\n';
            }
        }
    }
};