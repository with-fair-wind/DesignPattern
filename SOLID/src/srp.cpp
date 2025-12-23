#include <SRP/srp.h>

int main() {
    Journal journal("Daily Journal");
    journal.add(" First entry ");

    const auto journal_dir = boost::filesystem::current_path() / "journals";
    if (!boost::filesystem::exists(journal_dir)) {
        boost::filesystem::create_directories(journal_dir);
    }

    std::cout << "Journal directory: " << journal_dir.string() << '\n';
    std::cout << "Entry count: " << journal.entries().size() << '\n';

    for (const auto& entry : journal.entries()) {
        std::cout << entry << '\n';
    }
    PersistenceManager::save(journal, (journal_dir / "journal.txt").string());
    journal.add(" Second entry ");
    PersistenceManager::save(journal, (journal_dir / "journal.txt").string(), true);

    return journal.entries().empty() ? 1 : 0;
}