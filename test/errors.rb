def check_error(regex, expected_error)
    actual_output = `echo "" | #{$emregex} "#{regex}"`

    if actual_output != expected_error
        puts "TEST FAILED"
        puts "         regex: #{regex}"
        puts " actual output: #{actual_output}"
        puts "expected error: #{expected_error}"
        exit 1
    end
end

check_error "foo\\bar", "invalid escape sequence '\\b'"
