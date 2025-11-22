#!/bin/bash
echo
echo "--------------------EXPANSION--------------------------"
expansion=$(diff <(../minishell < expansion) <(bash < expansion))
status=$?
if [ $status -eq 0 ]; then
	echo "✅ OK!"
else
	echo "❌ KO!"
	echo "$expansion"
fi
echo
echo "---------------------HEREDOC---------------------------"
heredoc=$(diff <(../minishell < heredoc) <(bash < heredoc))
status=$?
if [ $status -eq 0 ]; then
	echo "✅ OK!"
else
	echo "❌ KO!"
	echo "$heredoc"
fi
echo
