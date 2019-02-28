// © 2019 Mohammad Julashokri
program p1;
const
max = 50 ;{max size of dfa stages 2^9}

type
a_type = array [0..8,0..8] of string;
alpha_type = array [0..7] of char;
d_s_type = array [0..max-1] of string;


var
infile:text;
outfile:text;
next,ch,stage,al:char;
q,qq,mq,staq,ql,ql1:string;
i,j,jj,k,h,hi,l,li,mm,num,q_l,max_s,max_ss,al_n,ql_n,ql_n1 : shortint;
alpha_n,sta_nfa_n,sta_dfa_n,sta_nfa_final_n,sta_dfa_final_n : shortint;
alpha : alpha_type;
nfa : a_type;
sta_nfa_final : array [0..8] of char;
sta_dfa_final : array [0..max-1] of shortint;
sta_dfa : d_s_type;
dfa : array [0..max-1,0..max-1] of shortint;
changes,check : boolean;



function m_a (ch:char;ar:alpha_type;alp_n:shortint):shortint;
var
hh : shortint;
begin
for hh :=1 to alp_n do
    if ar[hh] = ch then
       m_a := hh;
if ch = 'L' then
	m_a := 0;
end;


procedure dfa_s(ss:string;var dd:d_s_type;var num1:shortint;var 
max_s1:shortint);
var
hh1 : shortint;
find : boolean;
begin
find := false ;
for hh1 := 0 to max_s1  do
    if dd[hh1] = ss then
       begin
       num1 := hh1 ;
       find := true;
       end;
if not find then
    if ss <> '' then
       begin
       max_s1 := max_s1 + 1;
       num1 := max_s1;
       dd[num1] := dd[num1] + ss;
       end
       else
       num1 := -3;
end;


procedure merge (var s:string;t:string);
var
r,p,temp : string;
r1,p1,m : shortint;
begin
r1 := 1;
p1 := 1;
r := s;
p := t;
temp := '';
while (r1<=length(r)) and (p1<=length(p)) do
      begin
      if r[r1]<p[p1] then
         begin
         temp := temp + r[r1];
         r1 := r1 + 1;
         end
      else
      if r[r1]=p[p1] then
         begin
         temp := temp + r[r1];
         r1 := r1 +1;
         p1 := p1 +1;
         end
      else
      if p[p1]<r[r1] then
         begin
         temp := temp + p[p1];
         p1 := p1 +1;
         end;
      end;
for m:= r1 to length(r) do
    temp := temp + r[m];
for m:= p1 to length(p) do
    temp := temp + p[m];
s := temp ; 
end;


begin
assign (infile,'p1.in');
assign(outfile,'p1.out');
reset(infile);
rewrite(outfile);
alpha_n := 0;
while not eoln(infile) do
      begin
      read (infile,next);
      write(outfile,next);
        if next <> ',' then
         begin
         alpha_n := alpha_n + 1;
         alpha[alpha_n] := next;
         end;
      end;
readln(infile);
writeln(outfile);
sta_nfa_n := -1;
while not eoln(infile) do
      begin
      read(infile,next);
      if next = 'q' then
         sta_nfa_n := sta_nfa_n +1;
      end;
readln(infile);
readln(infile);  {for qo}
sta_nfa_final_n := -1;
while not eoln(infile) do
      begin
      read(infile,next);
      if next <> 'q' then
         if next <> ',' then
            begin
            sta_nfa_final_n := sta_nfa_final_n + 1;
            sta_nfa_final[sta_nfa_final_n] := next;
            end;
      end;
readln(infile);
{filling 
nfa------------------------------------------------------------}
for h := 0 to 8 do
    for k := 0 to 8 do
        nfa[h,k] := '';

stage := 'm';
while (not eof(infile)) do
begin
read(infile,stage);
if stage = 'd' then
begin
for h :=2 to 4 do
    read(infile,stage);
for h :=1 to 2 do
    read(infile,al);
al_n := m_a(al,alpha,alpha_n);
for h :=1 to 4 do
    read(infile,next);
read(infile,ch);
while ch <>'}' do
begin
     if (ch<>'q') and (ch<>',') then
        staq := staq + ch ;

read(infile,ch);
end;
nfa[ord(stage)-ord('0'),al_n] := staq;
staq := '';
readln(infile);
end;
end;
ql := '';
for i:=0 to sta_nfa_n do
    begin
    ql := '';
    while (ql <> nfa[i,0])  do
    begin
    ql := nfa[i,0];
    ql_n := length(ql);
    for l:=1 to ql_n do
        for li := 0 to alpha_n do
            merge(nfa[i,li],nfa[(ord(ql[l])-ord('0')),li]);
    end;
    for j:=1 to alpha_n do
        begin
        ql := '';
        while (ql <> nfa[i,j]) do
        begin
        ql := nfa[i,j] ;
        ql_n := length(ql);
        for h:=1 to ql_n do
            begin
            merge(nfa[i,j],nfa[(ord(ql[h])-ord('0')),0]);
            ql1 := nfa[(ord(ql[h])-ord('0')),0];
            ql_n1 := length(ql1);
            for hi := 1 to ql_n1 do
            if ( (ord(ql1[hi])-ord('0')) = i) then
                  continue;
            end;
        end;
        end;
    end;
for i := 0 to sta_nfa_n do
    for j := 0 to (alpha_n-1) do
        nfa[i,j] := nfa[i,j+1];
for i := 0 to (alpha_n-1) do
    alpha[i] := alpha[i+1];
alpha_n := alpha_n - 1 ;
{-----------------------------------------------------------------------}
for i:= 0 to max-1 do
    for j := 0 to max-1 do
        dfa[i,j] := -2;
max_s := 0;
sta_dfa[0] := '0';
max_ss := -1;
while max_ss <> max_s do
begin
max_ss := max_s;
jj :=0;
for j := jj to max_ss do
     for i := 0 to alpha_n do
         begin
         q := sta_dfa[j];
         mq := '';
         q_l := length(q);
         for h:= 1 to q_l do
             begin
             l := ord(q[h])-ord('0');
             qq := nfa[l,i];
             merge(mq,qq);  
             end;
         dfa_s(mq,sta_dfa,num,max_s);
         dfa[j,i] := num ;
         end;
if max_ss<>max_s then
   jj := max_ss;
end;
changes := false;
{for null stage}
for i:=0 to max_s do
    for j := 0 to alpha_n do
        if dfa[i,j] = -3 then
           changes := true;
if changes then
begin
max_s := max_s + 1;
for i:=0 to alpha_n do
    dfa[max_s,i] := max_s;
for i:=0 to max_s do
    for j:= 0 to alpha_n do
        if dfa[i,j] = -3 then
           dfa[i,j] := max_s;
end;
{dfa final states}
sta_dfa_final_n := 0 ;
for i:= 0 to max_s do
    begin
    q := sta_dfa[i];
    check := false ;
    q_l := length(q) ;
    for h:= 0 to sta_nfa_final_n do
         for j := 1 to q_l do
            if  q[j] = sta_nfa_final[h] then
                check := true;
    if check then
       begin
       sta_dfa_final_n := sta_dfa_final_n + 1;
       sta_dfa_final[sta_dfa_final_n] := i ;
       end;
    end;
{write out file-------------------------------------------------}
write(outfile,'q0');
for i := 1 to max_s do
    begin
    write(outfile,',');
    write(outfile,'q');
    write(outfile,i);
    end;
writeln(outfile);
writeln(outfile,'q0');
write(outfile,'q');
write(outfile,sta_dfa_final[1]);
for i := 2 to sta_dfa_final_n do
    begin
    write(outfile,',');
    write(outfile,'q');
    write(outfile,sta_dfa_final[i]);
    end;
writeln(outfile);
for i := 0 to max_s do
    for j:= 0 to alpha_n do
        begin
        write(outfile,'d(q');
        write(outfile,i);
        write(outfile,',');
        write(outfile,alpha[j]);
        write(outfile,') = q');
        write(outfile,dfa[i,j]);
        writeln(outfile);
        end;
close(outfile);
end.
