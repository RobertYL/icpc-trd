set cin ai is ts=2 sw=2 tm=50 nu bg=dark ru bo=all mouse=a | sy on
" Select region and then type :Hash to hash your selection.
" Useful for verifying that there aren't mistypes.
ca Hash w !cpp -dD -P -fpreprocessed \| tr -d '[:space:]' \
 \| md5sum \| cut -c-6
