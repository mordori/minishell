#!/bin/bash
echo
echo "--------------------EXPANSION--------------------------"
expansion=$(diff <(./minishell < tests/expansion) <(bash < tests/expansion))
status=$?
if [ $status -eq 0 ]; then
	echo "✅ OK!"
else
	echo "❌ KO!"
	echo "$expansion"
fi
echo
echo "---------------------HEREDOC---------------------------"
heredoc=$(diff <(./minishell < tests/heredoc) <(bash < tests/heredoc))
status=$?
if [ $status -eq 0 ]; then
	echo "✅ OK!"
else
	echo "❌ KO!"
	echo "$heredoc"
fi
echo
