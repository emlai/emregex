require "benchmark"

TIME_MULTIPLIER = 1

def measure(regex, allowed_time, input)
    allowed_time *= TIME_MULTIPLIER
    elapsed_time = nil

    10.times do
        elapsed_time = Benchmark.realtime { `echo "#{input}" | #{$emregex} "#{regex}"` }
        return if elapsed_time <= allowed_time
    end

    puts "TEST FAILED"
    puts "       regex: #{regex}"
    puts "elapsed time: #{elapsed_time} seconds"
    puts "allowed time: #{allowed_time} seconds"
    exit 1
end

measure "a(bc)?d*d", 0.012, ("abcdddddddddaddddddddd" * 1000)
measure "(foo)*", 0.075, ("foo" * 10000)
measure "a*b", 0.015, ("aa" * 10000 + "b")
