cribdrag
Released after LOL Bitcoin party at DEF CON 21
Daniel Crowley <dcrowley@trustwave.com>
http://www.trustwave.com

INTRODUCTION
============

cribdrag is a script for performing crib dragging attacks against
ciphertext encrypted using an XOR operation with a predictable key.

This script can be used to cryptanalyze:
One-Time Pad with reused key (XOR two ciphertexts together)
Any stream cipher with reused key (XOR two ciphertexts together)
Single character XOR
Multiple character XOR

REQUIREMENTS
============

python 3.2+

USAGE
=====

python xorstrings.py &lt;ascii hex encoded data&gt; &lt;ascii hex encoded data&gt;

python cribdrag.py [-c charset] &lt;ascii hex encoded ciphertext&gt;

COPYRIGHT
=========

cribdrag - Interactive crib dragging tool
Daniel Crowley
Copyright (C) 2013 Trustwave Holdings, Inc.
 
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
 
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>
