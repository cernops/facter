# frozen_string_literal: true

module Facts
  module Freebsd
    module Processors
      class Speed
        FACT_NAME = 'processors.speed'

        def call_the_resolver
          fact_value = Facter::Resolvers::Freebsd::Processors.resolve(:speed)
          speed = Facter::Util::Facts::UnitConverter.hertz_to_human_readable(fact_value)
          Facter::ResolvedFact.new(FACT_NAME, speed)
        end
      end
    end
  end
end
