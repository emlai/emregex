require "benchmark"

TIME_MULTIPLIER = 1

def measure(regex, allowed_time, input)
    allowed_time *= TIME_MULTIPLIER
    elapsed_time = Benchmark.realtime { `echo "#{input}" | #{$emregex} "#{regex}"` }

    if elapsed_time > allowed_time
        puts "TEST FAILED"
        puts "       regex: #{regex}"
        puts "elapsed time: #{elapsed_time} seconds"
        puts "allowed time: #{allowed_time} seconds"
        exit 1
    end
end

measure "a(bc)?d*d", 0.085, ("abcdddddddddaddddddddd" * 10000)
measure "(foo)*", 0.075, ("foo" * 10000)
measure "a*b", 0.08, ("aa" * 100000 + "b")
