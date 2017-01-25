regex = "a(bc)?d*"
expected_ast = "(seq a (opt (seq b c)) (star d))"
actual_ast = `#{$emregex} "#{regex}" --print-ast`

if actual_ast != expected_ast
    puts "TEST FAILED"
    puts "       regex: #{regex}"
    puts "  actual AST: #{actual_ast}"
    puts "expected AST: #{expected_ast}"
    exit 1
end
