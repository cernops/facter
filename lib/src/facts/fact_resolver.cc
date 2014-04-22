#include <facts/fact_resolver.hpp>
#include <facts/fact_map.hpp>
#include <re2/re2.h>

using namespace std;
using namespace re2;

namespace cfacter { namespace facts {

    fact_resolver::fact_resolver(vector<string>&& names, vector<string> const& patterns) :
        _names(move(names)),
        _resolving(false)
    {
        for (auto const& pattern : patterns) {
            auto regex = unique_ptr<RE2>(new RE2(pattern));
            if (!regex->error().empty()) {
                throw invalid_name_pattern_exception(regex->error());
            }
            _regexes.push_back(move(regex));
        }
    }

    fact_resolver::~fact_resolver()
    {
    }

    void fact_resolver::resolve(fact_map& facts)
    {
        if (_resolving) {
            throw circular_resolution_exception("a cycle in fact resolution was detected.");
        }
        cycle_guard guard(_resolving);
        return resolve_facts(facts);
    }

    bool fact_resolver::can_resolve(string const& name) const
    {
        // Check to see if any of our regexes match
        for (auto const& regex : _regexes) {
            if (RE2::PartialMatch(name, *regex)) {
                return true;
            }
        }
        return false;
    }

}}  // namespace cfacter::facts
