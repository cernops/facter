# frozen_string_literal: true

module Facts
  module Macosx
    module Processors
      class Cores
        FACT_NAME = 'processors.cores'

        def call_the_resolver
          fact_value = Facter::Resolvers::Macosx::Processors.resolve(:cores_per_socket)
          Facter::ResolvedFact.new(FACT_NAME, fact_value)
        end
      end
    end
  end
end
