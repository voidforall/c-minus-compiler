* C-- Compilation to TM code
* Standard prelude:
  0:     LD  6,0(0) 	load maxaddress from location 0
  1:     ST  0,0(0) 	clear loation 0
* End of standard prelude:
* Begin generating built-ins
* Generate built-in input
  5:     ST  0,-1(4) 	save return address in fp + retFO
  6:     IN  0,0,0 	read input
  7:     LD  7,-1(4) 	return to caller
* Generate built-in output
  8:     ST  0,-1(4) 	save return address in fp + retFO
  9:     LD  0,-2(4) 	get x for output
 10:    OUT  0,0,0 	output x
 11:     LD  7,-1(4) 	return to caller
* End generating built-in
* --> Function (qsort)
 12:     ST  0,-1(4) 	save return address in fp + retFO
* -> Begin function body
* --> DeclVar
* <-- DeclVar
* --> DeclVar
* <-- DeclVar
* --> DeclVar
* <-- DeclVar
* --> DeclVar
* <-- DeclVar
* --> DeclVar
* <-- DeclVar
* --> Assign
* --> ExprId
 13:    LDC  0,-6(0) 	ExprId: load id offset to ac
 14:    ADD  0,4,0 	ExprId: fp + offset = base address
 15:    LDA  0,0(0) 	ExprId: load id address
* <-- ExprId
 16:     ST  0,-11(4) 	assign: push id(addr) to fp
* --> ExprId
 17:    LDC  0,-3(0) 	ExprId: load id offset to ac
 18:    ADD  0,4,0 	ExprId: fp + offset = base address
 19:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
 20:     LD  1,-11(4) 	assign: load id(addr) to ac1
 21:     ST  0,0(1) 	assign: assign expr(ac)->id(ac1)
* <-- Assign
* --> Assign
* --> ExprId
 22:    LDC  0,-7(0) 	ExprId: load id offset to ac
 23:    ADD  0,4,0 	ExprId: fp + offset = base address
 24:    LDA  0,0(0) 	ExprId: load id address
* <-- ExprId
 25:     ST  0,-11(4) 	assign: push id(addr) to fp
* --> ExprId
 26:    LDC  0,-4(0) 	ExprId: load id offset to ac
 27:    ADD  0,4,0 	ExprId: fp + offset = base address
 28:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
 29:     LD  1,-11(4) 	assign: load id(addr) to ac1
 30:     ST  0,0(1) 	assign: assign expr(ac)->id(ac1)
* <-- Assign
* --> Assign
* --> ExprId
 31:    LDC  0,-5(0) 	ExprId: load id offset to ac
 32:    ADD  0,4,0 	ExprId: fp + offset = base address
 33:    LDA  0,0(0) 	ExprId: load id address
* <-- ExprId
 34:     ST  0,-11(4) 	assign: push id(addr) to fp
* --> ExprId
 35:    LDC  0,-2(0) 	ExprId: load id offset to ac
 36:    ADD  0,4,0 	ExprId: fp + offset = base address
 37:     LD  0,0(0) 	load absolute address
 38:     ST  0,-12(4) 	ExprId: push base address to mp
* --> ExprId
 39:    LDC  0,-3(0) 	ExprId: load id offset to ac
 40:    ADD  0,4,0 	ExprId: fp + offset = base address
 41:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
 42:     LD  1,-12(4) 	ExprId: load base address to ac1
 43:    SUB  0,1,0 	ExprId: base address - index = index address
 44:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
 45:     LD  1,-11(4) 	assign: load id(addr) to ac1
 46:     ST  0,0(1) 	assign: assign expr(ac)->id(ac1)
* <-- Assign
* --> Assign
* --> ExprId
 47:    LDC  0,-8(0) 	ExprId: load id offset to ac
 48:    ADD  0,4,0 	ExprId: fp + offset = base address
 49:    LDA  0,0(0) 	ExprId: load id address
* <-- ExprId
 50:     ST  0,-11(4) 	assign: push id(addr) to fp
* --> Const
 51:    LDC  0,0(0) 	Const: load val to ac
* <-- Const
 52:     LD  1,-11(4) 	assign: load id(addr) to ac1
 53:     ST  0,0(1) 	assign: assign expr(ac)->id(ac1)
* <-- Assign
* --> While
* --> Op
* --> ExprId
 54:    LDC  0,-6(0) 	ExprId: load id offset to ac
 55:    ADD  0,4,0 	ExprId: fp + offset = base address
 56:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
 57:     ST  0,-11(4) 	op: push operand1 to mp
* --> ExprId
 58:    LDC  0,-7(0) 	ExprId: load id offset to ac
 59:    ADD  0,4,0 	ExprId: fp + offset = base address
 60:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
 61:     LD  1,-11(4) 	op: load operand1 from mp
 62:    SUB  0,1,0 	op: <
 63:    JLT  0,2(7) 	if <, pc = pc + 2
 64:    LDC  0,0(0) 	if false, ac = 0
 65:    LDA  7,1(7) 	if false, skip next
 66:    LDC  0,1(0) 	if true, ac = 1
* <-- Op
* --> If
* --> Op
* --> ExprId
 68:    LDC  0,-8(0) 	ExprId: load id offset to ac
 69:    ADD  0,4,0 	ExprId: fp + offset = base address
 70:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
 71:     ST  0,-11(4) 	op: push operand1 to mp
* --> Const
 72:    LDC  0,0(0) 	Const: load val to ac
* <-- Const
 73:     LD  1,-11(4) 	op: load operand1 from mp
 74:    SUB  0,1,0 	op: ==
 75:    JEQ  0,2(7) 	if ==, pc = pc + 2
 76:    LDC  0,0(0) 	if false, ac = 0
 77:    LDA  7,1(7) 	if false, skip next
 78:    LDC  0,1(0) 	if true, ac = 1
* <-- Op
* --> If
* --> Op
* --> ExprId
 80:    LDC  0,-2(0) 	ExprId: load id offset to ac
 81:    ADD  0,4,0 	ExprId: fp + offset = base address
 82:     LD  0,0(0) 	load absolute address
 83:     ST  0,-11(4) 	ExprId: push base address to mp
* --> ExprId
 84:    LDC  0,-7(0) 	ExprId: load id offset to ac
 85:    ADD  0,4,0 	ExprId: fp + offset = base address
 86:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
 87:     LD  1,-11(4) 	ExprId: load base address to ac1
 88:    SUB  0,1,0 	ExprId: base address - index = index address
 89:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
 90:     ST  0,-11(4) 	op: push operand1 to mp
* --> ExprId
 91:    LDC  0,-5(0) 	ExprId: load id offset to ac
 92:    ADD  0,4,0 	ExprId: fp + offset = base address
 93:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
 94:     LD  1,-11(4) 	op: load operand1 from mp
 95:    SUB  0,1,0 	op: <
 96:    JLT  0,2(7) 	if <, pc = pc + 2
 97:    LDC  0,0(0) 	if false, ac = 0
 98:    LDA  7,1(7) 	if false, skip next
 99:    LDC  0,1(0) 	if true, ac = 1
* <-- Op
* --> Assign
* --> ExprId
101:    LDC  0,-9(0) 	ExprId: load id offset to ac
102:    ADD  0,4,0 	ExprId: fp + offset = base address
103:    LDA  0,0(0) 	ExprId: load id address
* <-- ExprId
104:     ST  0,-11(4) 	assign: push id(addr) to fp
* --> ExprId
105:    LDC  0,-2(0) 	ExprId: load id offset to ac
106:    ADD  0,4,0 	ExprId: fp + offset = base address
107:     LD  0,0(0) 	load absolute address
108:     ST  0,-12(4) 	ExprId: push base address to mp
* --> ExprId
109:    LDC  0,-7(0) 	ExprId: load id offset to ac
110:    ADD  0,4,0 	ExprId: fp + offset = base address
111:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
112:     LD  1,-12(4) 	ExprId: load base address to ac1
113:    SUB  0,1,0 	ExprId: base address - index = index address
114:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
115:     LD  1,-11(4) 	assign: load id(addr) to ac1
116:     ST  0,0(1) 	assign: assign expr(ac)->id(ac1)
* <-- Assign
* --> Assign
* --> ExprId
117:    LDC  0,-2(0) 	ExprId: load id offset to ac
118:    ADD  0,4,0 	ExprId: fp + offset = base address
119:     LD  0,0(0) 	load absolute address
120:     ST  0,-11(4) 	ExprId: push base address to mp
* --> ExprId
121:    LDC  0,-7(0) 	ExprId: load id offset to ac
122:    ADD  0,4,0 	ExprId: fp + offset = base address
123:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
124:     LD  1,-11(4) 	ExprId: load base address to ac1
125:    SUB  0,1,0 	ExprId: base address - index = index address
126:    LDA  0,0(0) 	ExprId: load id address
* <-- ExprId
127:     ST  0,-11(4) 	assign: push id(addr) to fp
* --> ExprId
128:    LDC  0,-2(0) 	ExprId: load id offset to ac
129:    ADD  0,4,0 	ExprId: fp + offset = base address
130:     LD  0,0(0) 	load absolute address
131:     ST  0,-12(4) 	ExprId: push base address to mp
* --> ExprId
132:    LDC  0,-6(0) 	ExprId: load id offset to ac
133:    ADD  0,4,0 	ExprId: fp + offset = base address
134:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
135:     LD  1,-12(4) 	ExprId: load base address to ac1
136:    SUB  0,1,0 	ExprId: base address - index = index address
137:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
138:     LD  1,-11(4) 	assign: load id(addr) to ac1
139:     ST  0,0(1) 	assign: assign expr(ac)->id(ac1)
* <-- Assign
* --> Assign
* --> ExprId
140:    LDC  0,-2(0) 	ExprId: load id offset to ac
141:    ADD  0,4,0 	ExprId: fp + offset = base address
142:     LD  0,0(0) 	load absolute address
143:     ST  0,-11(4) 	ExprId: push base address to mp
* --> ExprId
144:    LDC  0,-6(0) 	ExprId: load id offset to ac
145:    ADD  0,4,0 	ExprId: fp + offset = base address
146:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
147:     LD  1,-11(4) 	ExprId: load base address to ac1
148:    SUB  0,1,0 	ExprId: base address - index = index address
149:    LDA  0,0(0) 	ExprId: load id address
* <-- ExprId
150:     ST  0,-11(4) 	assign: push id(addr) to fp
* --> ExprId
151:    LDC  0,-9(0) 	ExprId: load id offset to ac
152:    ADD  0,4,0 	ExprId: fp + offset = base address
153:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
154:     LD  1,-11(4) 	assign: load id(addr) to ac1
155:     ST  0,0(1) 	assign: assign expr(ac)->id(ac1)
* <-- Assign
* --> Assign
* --> ExprId
156:    LDC  0,-8(0) 	ExprId: load id offset to ac
157:    ADD  0,4,0 	ExprId: fp + offset = base address
158:    LDA  0,0(0) 	ExprId: load id address
* <-- ExprId
159:     ST  0,-11(4) 	assign: push id(addr) to fp
* --> Const
160:    LDC  0,1(0) 	Const: load val to ac
* <-- Const
161:     LD  1,-11(4) 	assign: load id(addr) to ac1
162:     ST  0,0(1) 	assign: assign expr(ac)->id(ac1)
* <-- Assign
* --> Assign
* --> ExprId
164:    LDC  0,-7(0) 	ExprId: load id offset to ac
165:    ADD  0,4,0 	ExprId: fp + offset = base address
166:    LDA  0,0(0) 	ExprId: load id address
* <-- ExprId
167:     ST  0,-11(4) 	assign: push id(addr) to fp
* --> Op
* --> ExprId
168:    LDC  0,-7(0) 	ExprId: load id offset to ac
169:    ADD  0,4,0 	ExprId: fp + offset = base address
170:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
171:     ST  0,-12(4) 	op: push operand1 to mp
* --> Const
172:    LDC  0,1(0) 	Const: load val to ac
* <-- Const
173:     LD  1,-12(4) 	op: load operand1 from mp
174:    SUB  0,1,0 	op: Minus
* <-- Op
175:     LD  1,-11(4) 	assign: load id(addr) to ac1
176:     ST  0,0(1) 	assign: assign expr(ac)->id(ac1)
* <-- Assign
100:    JEQ  0,63(7) 	If false, jump to else part
163:    LDA  7,13(7) 	Jump to the end
* <-- If
* --> If
* --> Op
* --> ExprId
178:    LDC  0,-2(0) 	ExprId: load id offset to ac
179:    ADD  0,4,0 	ExprId: fp + offset = base address
180:     LD  0,0(0) 	load absolute address
181:     ST  0,-11(4) 	ExprId: push base address to mp
* --> ExprId
182:    LDC  0,-6(0) 	ExprId: load id offset to ac
183:    ADD  0,4,0 	ExprId: fp + offset = base address
184:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
185:     LD  1,-11(4) 	ExprId: load base address to ac1
186:    SUB  0,1,0 	ExprId: base address - index = index address
187:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
188:     ST  0,-11(4) 	op: push operand1 to mp
* --> ExprId
189:    LDC  0,-5(0) 	ExprId: load id offset to ac
190:    ADD  0,4,0 	ExprId: fp + offset = base address
191:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
192:     LD  1,-11(4) 	op: load operand1 from mp
193:    SUB  0,1,0 	op: >
194:    JGT  0,2(7) 	if >, pc = pc + 2
195:    LDC  0,0(0) 	if false, ac = 0
196:    LDA  7,1(7) 	if false, skip next
197:    LDC  0,1(0) 	if true, ac = 1
* <-- Op
* --> Assign
* --> ExprId
199:    LDC  0,-9(0) 	ExprId: load id offset to ac
200:    ADD  0,4,0 	ExprId: fp + offset = base address
201:    LDA  0,0(0) 	ExprId: load id address
* <-- ExprId
202:     ST  0,-11(4) 	assign: push id(addr) to fp
* --> ExprId
203:    LDC  0,-2(0) 	ExprId: load id offset to ac
204:    ADD  0,4,0 	ExprId: fp + offset = base address
205:     LD  0,0(0) 	load absolute address
206:     ST  0,-12(4) 	ExprId: push base address to mp
* --> ExprId
207:    LDC  0,-7(0) 	ExprId: load id offset to ac
208:    ADD  0,4,0 	ExprId: fp + offset = base address
209:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
210:     LD  1,-12(4) 	ExprId: load base address to ac1
211:    SUB  0,1,0 	ExprId: base address - index = index address
212:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
213:     LD  1,-11(4) 	assign: load id(addr) to ac1
214:     ST  0,0(1) 	assign: assign expr(ac)->id(ac1)
* <-- Assign
* --> Assign
* --> ExprId
215:    LDC  0,-2(0) 	ExprId: load id offset to ac
216:    ADD  0,4,0 	ExprId: fp + offset = base address
217:     LD  0,0(0) 	load absolute address
218:     ST  0,-11(4) 	ExprId: push base address to mp
* --> ExprId
219:    LDC  0,-7(0) 	ExprId: load id offset to ac
220:    ADD  0,4,0 	ExprId: fp + offset = base address
221:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
222:     LD  1,-11(4) 	ExprId: load base address to ac1
223:    SUB  0,1,0 	ExprId: base address - index = index address
224:    LDA  0,0(0) 	ExprId: load id address
* <-- ExprId
225:     ST  0,-11(4) 	assign: push id(addr) to fp
* --> ExprId
226:    LDC  0,-2(0) 	ExprId: load id offset to ac
227:    ADD  0,4,0 	ExprId: fp + offset = base address
228:     LD  0,0(0) 	load absolute address
229:     ST  0,-12(4) 	ExprId: push base address to mp
* --> ExprId
230:    LDC  0,-6(0) 	ExprId: load id offset to ac
231:    ADD  0,4,0 	ExprId: fp + offset = base address
232:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
233:     LD  1,-12(4) 	ExprId: load base address to ac1
234:    SUB  0,1,0 	ExprId: base address - index = index address
235:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
236:     LD  1,-11(4) 	assign: load id(addr) to ac1
237:     ST  0,0(1) 	assign: assign expr(ac)->id(ac1)
* <-- Assign
* --> Assign
* --> ExprId
238:    LDC  0,-2(0) 	ExprId: load id offset to ac
239:    ADD  0,4,0 	ExprId: fp + offset = base address
240:     LD  0,0(0) 	load absolute address
241:     ST  0,-11(4) 	ExprId: push base address to mp
* --> ExprId
242:    LDC  0,-6(0) 	ExprId: load id offset to ac
243:    ADD  0,4,0 	ExprId: fp + offset = base address
244:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
245:     LD  1,-11(4) 	ExprId: load base address to ac1
246:    SUB  0,1,0 	ExprId: base address - index = index address
247:    LDA  0,0(0) 	ExprId: load id address
* <-- ExprId
248:     ST  0,-11(4) 	assign: push id(addr) to fp
* --> ExprId
249:    LDC  0,-9(0) 	ExprId: load id offset to ac
250:    ADD  0,4,0 	ExprId: fp + offset = base address
251:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
252:     LD  1,-11(4) 	assign: load id(addr) to ac1
253:     ST  0,0(1) 	assign: assign expr(ac)->id(ac1)
* <-- Assign
* --> Assign
* --> ExprId
254:    LDC  0,-8(0) 	ExprId: load id offset to ac
255:    ADD  0,4,0 	ExprId: fp + offset = base address
256:    LDA  0,0(0) 	ExprId: load id address
* <-- ExprId
257:     ST  0,-11(4) 	assign: push id(addr) to fp
* --> Const
258:    LDC  0,0(0) 	Const: load val to ac
* <-- Const
259:     LD  1,-11(4) 	assign: load id(addr) to ac1
260:     ST  0,0(1) 	assign: assign expr(ac)->id(ac1)
* <-- Assign
* --> Assign
* --> ExprId
262:    LDC  0,-6(0) 	ExprId: load id offset to ac
263:    ADD  0,4,0 	ExprId: fp + offset = base address
264:    LDA  0,0(0) 	ExprId: load id address
* <-- ExprId
265:     ST  0,-11(4) 	assign: push id(addr) to fp
* --> Op
* --> ExprId
266:    LDC  0,-6(0) 	ExprId: load id offset to ac
267:    ADD  0,4,0 	ExprId: fp + offset = base address
268:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
269:     ST  0,-12(4) 	op: push operand1 to mp
* --> Const
270:    LDC  0,1(0) 	Const: load val to ac
* <-- Const
271:     LD  1,-12(4) 	op: load operand1 from mp
272:    ADD  0,1,0 	op: Plus
* <-- Op
273:     LD  1,-11(4) 	assign: load id(addr) to ac1
274:     ST  0,0(1) 	assign: assign expr(ac)->id(ac1)
* <-- Assign
198:    JEQ  0,63(7) 	If false, jump to else part
261:    LDA  7,13(7) 	Jump to the end
* <-- If
 79:    JEQ  0,98(7) 	If false, jump to else part
177:    LDA  7,97(7) 	Jump to the end
* <-- If
275:    LDA  7,-222(7) 	Jump to while condition
 67:    JEQ  0,208(7) 	If false, end loop
* <-- While
* --> If
* --> Op
* --> ExprId
276:    LDC  0,-3(0) 	ExprId: load id offset to ac
277:    ADD  0,4,0 	ExprId: fp + offset = base address
278:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
279:     ST  0,-11(4) 	op: push operand1 to mp
* --> ExprId
280:    LDC  0,-4(0) 	ExprId: load id offset to ac
281:    ADD  0,4,0 	ExprId: fp + offset = base address
282:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
283:     LD  1,-11(4) 	op: load operand1 from mp
284:    SUB  0,1,0 	op: <
285:    JLT  0,2(7) 	if <, pc = pc + 2
286:    LDC  0,0(0) 	if false, ac = 0
287:    LDA  7,1(7) 	if false, skip next
288:    LDC  0,1(0) 	if true, ac = 1
* <-- Op
* --> Calling (qsort)
* --> ExprId
290:    LDC  0,-2(0) 	ExprId: load id offset to ac
291:    ADD  0,4,0 	ExprId: fp + offset = base address
292:     LD  0,0(0) 	load absolute address
293:    LDA  0,0(0) 	ExprId: load id address
* <-- ExprId
294:     ST  0,-13(4) 	store parameter 0
* --> ExprId
295:    LDC  0,-3(0) 	ExprId: load id offset to ac
296:    ADD  0,4,0 	ExprId: fp + offset = base address
297:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
298:     ST  0,-14(4) 	store parameter 1
* --> Op
* --> ExprId
299:    LDC  0,-6(0) 	ExprId: load id offset to ac
300:    ADD  0,4,0 	ExprId: fp + offset = base address
301:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
302:     ST  0,-12(4) 	op: push operand1 to mp
* --> Const
303:    LDC  0,1(0) 	Const: load val to ac
* <-- Const
304:     LD  1,-12(4) 	op: load operand1 from mp
305:    SUB  0,1,0 	op: Minus
* <-- Op
306:     ST  0,-15(4) 	store parameter 2
307:     ST  4,-11(4) 	store old frame pointer
308:    LDA  4,-11(4) 	push new frame
309:    LDA  0,1(7) 	save return address in ac
310:    LDA  7,-299(7) 	jump to the function
311:     LD  4,0(4) 	restore frame pointer
* <-- Calling (qsort)
* --> Calling (qsort)
* --> ExprId
312:    LDC  0,-2(0) 	ExprId: load id offset to ac
313:    ADD  0,4,0 	ExprId: fp + offset = base address
314:     LD  0,0(0) 	load absolute address
315:    LDA  0,0(0) 	ExprId: load id address
* <-- ExprId
316:     ST  0,-13(4) 	store parameter 0
* --> Op
* --> ExprId
317:    LDC  0,-6(0) 	ExprId: load id offset to ac
318:    ADD  0,4,0 	ExprId: fp + offset = base address
319:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
320:     ST  0,-12(4) 	op: push operand1 to mp
* --> Const
321:    LDC  0,1(0) 	Const: load val to ac
* <-- Const
322:     LD  1,-12(4) 	op: load operand1 from mp
323:    ADD  0,1,0 	op: Plus
* <-- Op
324:     ST  0,-14(4) 	store parameter 1
* --> ExprId
325:    LDC  0,-4(0) 	ExprId: load id offset to ac
326:    ADD  0,4,0 	ExprId: fp + offset = base address
327:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
328:     ST  0,-15(4) 	store parameter 2
329:     ST  4,-11(4) 	store old frame pointer
330:    LDA  4,-11(4) 	push new frame
331:    LDA  0,1(7) 	save return address in ac
332:    LDA  7,-321(7) 	jump to the function
333:     LD  4,0(4) 	restore frame pointer
* <-- Calling (qsort)
289:    JEQ  0,44(7) 	If false, jump to the end
* <-- If
* <- End function body
334:     LD  7,-1(4) 	return to caller
* <-- Function (qsort)
* --> Function (main)
335:     ST  0,-1(4) 	save return address in fp + retFO
* -> Begin function body
* --> DeclVar
* <-- DeclVar
* --> DeclVar
* <-- DeclVar
* --> Assign
* --> ExprId
336:    LDC  0,-12(0) 	ExprId: load id offset to ac
337:    ADD  0,4,0 	ExprId: fp + offset = base address
338:    LDA  0,0(0) 	ExprId: load id address
* <-- ExprId
339:     ST  0,-14(4) 	assign: push id(addr) to fp
* --> Const
340:    LDC  0,0(0) 	Const: load val to ac
* <-- Const
341:     LD  1,-14(4) 	assign: load id(addr) to ac1
342:     ST  0,0(1) 	assign: assign expr(ac)->id(ac1)
* <-- Assign
* --> While
* --> Op
* --> ExprId
343:    LDC  0,-12(0) 	ExprId: load id offset to ac
344:    ADD  0,4,0 	ExprId: fp + offset = base address
345:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
346:     ST  0,-14(4) 	op: push operand1 to mp
* --> Const
347:    LDC  0,10(0) 	Const: load val to ac
* <-- Const
348:     LD  1,-14(4) 	op: load operand1 from mp
349:    SUB  0,1,0 	op: <
350:    JLT  0,2(7) 	if <, pc = pc + 2
351:    LDC  0,0(0) 	if false, ac = 0
352:    LDA  7,1(7) 	if false, skip next
353:    LDC  0,1(0) 	if true, ac = 1
* <-- Op
* --> Assign
* --> ExprId
355:    LDC  0,-2(0) 	ExprId: load id offset to ac
356:    ADD  0,4,0 	ExprId: fp + offset = base address
357:     ST  0,-14(4) 	ExprId: push base address to mp
* --> ExprId
358:    LDC  0,-12(0) 	ExprId: load id offset to ac
359:    ADD  0,4,0 	ExprId: fp + offset = base address
360:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
361:     LD  1,-14(4) 	ExprId: load base address to ac1
362:    SUB  0,1,0 	ExprId: base address - index = index address
363:    LDA  0,0(0) 	ExprId: load id address
* <-- ExprId
364:     ST  0,-14(4) 	assign: push id(addr) to fp
* --> Calling (input)
365:     ST  4,-15(4) 	store old frame pointer
366:    LDA  4,-15(4) 	push new frame
367:    LDA  0,1(7) 	save return address in ac
368:    LDA  7,-364(7) 	jump to the function
369:     LD  4,0(4) 	restore frame pointer
* <-- Calling (input)
370:     LD  1,-14(4) 	assign: load id(addr) to ac1
371:     ST  0,0(1) 	assign: assign expr(ac)->id(ac1)
* <-- Assign
* --> Assign
* --> ExprId
372:    LDC  0,-12(0) 	ExprId: load id offset to ac
373:    ADD  0,4,0 	ExprId: fp + offset = base address
374:    LDA  0,0(0) 	ExprId: load id address
* <-- ExprId
375:     ST  0,-14(4) 	assign: push id(addr) to fp
* --> Op
* --> ExprId
376:    LDC  0,-12(0) 	ExprId: load id offset to ac
377:    ADD  0,4,0 	ExprId: fp + offset = base address
378:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
379:     ST  0,-15(4) 	op: push operand1 to mp
* --> Const
380:    LDC  0,1(0) 	Const: load val to ac
* <-- Const
381:     LD  1,-15(4) 	op: load operand1 from mp
382:    ADD  0,1,0 	op: Plus
* <-- Op
383:     LD  1,-14(4) 	assign: load id(addr) to ac1
384:     ST  0,0(1) 	assign: assign expr(ac)->id(ac1)
* <-- Assign
385:    LDA  7,-43(7) 	Jump to while condition
354:    JEQ  0,31(7) 	If false, end loop
* <-- While
* --> Calling (qsort)
* --> ExprId
386:    LDC  0,-2(0) 	ExprId: load id offset to ac
387:    ADD  0,4,0 	ExprId: fp + offset = base address
388:    LDA  0,0(0) 	ExprId: load id address
* <-- ExprId
389:     ST  0,-16(4) 	store parameter 0
* --> Const
390:    LDC  0,0(0) 	Const: load val to ac
* <-- Const
391:     ST  0,-17(4) 	store parameter 1
* --> Const
392:    LDC  0,9(0) 	Const: load val to ac
* <-- Const
393:     ST  0,-18(4) 	store parameter 2
394:     ST  4,-14(4) 	store old frame pointer
395:    LDA  4,-14(4) 	push new frame
396:    LDA  0,1(7) 	save return address in ac
397:    LDA  7,-386(7) 	jump to the function
398:     LD  4,0(4) 	restore frame pointer
* <-- Calling (qsort)
* --> Assign
* --> ExprId
399:    LDC  0,-12(0) 	ExprId: load id offset to ac
400:    ADD  0,4,0 	ExprId: fp + offset = base address
401:    LDA  0,0(0) 	ExprId: load id address
* <-- ExprId
402:     ST  0,-14(4) 	assign: push id(addr) to fp
* --> Const
403:    LDC  0,0(0) 	Const: load val to ac
* <-- Const
404:     LD  1,-14(4) 	assign: load id(addr) to ac1
405:     ST  0,0(1) 	assign: assign expr(ac)->id(ac1)
* <-- Assign
* --> While
* --> Op
* --> ExprId
406:    LDC  0,-12(0) 	ExprId: load id offset to ac
407:    ADD  0,4,0 	ExprId: fp + offset = base address
408:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
409:     ST  0,-14(4) 	op: push operand1 to mp
* --> Const
410:    LDC  0,10(0) 	Const: load val to ac
* <-- Const
411:     LD  1,-14(4) 	op: load operand1 from mp
412:    SUB  0,1,0 	op: <
413:    JLT  0,2(7) 	if <, pc = pc + 2
414:    LDC  0,0(0) 	if false, ac = 0
415:    LDA  7,1(7) 	if false, skip next
416:    LDC  0,1(0) 	if true, ac = 1
* <-- Op
* --> Calling (output)
* --> ExprId
418:    LDC  0,-2(0) 	ExprId: load id offset to ac
419:    ADD  0,4,0 	ExprId: fp + offset = base address
420:     ST  0,-15(4) 	ExprId: push base address to mp
* --> ExprId
421:    LDC  0,-12(0) 	ExprId: load id offset to ac
422:    ADD  0,4,0 	ExprId: fp + offset = base address
423:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
424:     LD  1,-15(4) 	ExprId: load base address to ac1
425:    SUB  0,1,0 	ExprId: base address - index = index address
426:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
427:     ST  0,-16(4) 	store parameter 0
428:     ST  4,-14(4) 	store old frame pointer
429:    LDA  4,-14(4) 	push new frame
430:    LDA  0,1(7) 	save return address in ac
431:    LDA  7,-424(7) 	jump to the function
432:     LD  4,0(4) 	restore frame pointer
* <-- Calling (output)
* --> Assign
* --> ExprId
433:    LDC  0,-12(0) 	ExprId: load id offset to ac
434:    ADD  0,4,0 	ExprId: fp + offset = base address
435:    LDA  0,0(0) 	ExprId: load id address
* <-- ExprId
436:     ST  0,-14(4) 	assign: push id(addr) to fp
* --> Op
* --> ExprId
437:    LDC  0,-12(0) 	ExprId: load id offset to ac
438:    ADD  0,4,0 	ExprId: fp + offset = base address
439:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
440:     ST  0,-15(4) 	op: push operand1 to mp
* --> Const
441:    LDC  0,1(0) 	Const: load val to ac
* <-- Const
442:     LD  1,-15(4) 	op: load operand1 from mp
443:    ADD  0,1,0 	op: Plus
* <-- Op
444:     LD  1,-14(4) 	assign: load id(addr) to ac1
445:     ST  0,0(1) 	assign: assign expr(ac)->id(ac1)
* <-- Assign
446:    LDA  7,-41(7) 	Jump to while condition
417:    JEQ  0,29(7) 	If false, end loop
* <-- While
* --> Return
* --> Const
447:    LDC  0,0(0) 	Const: load val to ac
* <-- Const
* <-- Return
* <- End function body
448:     LD  7,-1(4) 	return to caller
* <-- Function (main)
* End of execution
  2:    LDA  4,-2(6) 	load initial frame pointer
  3:    LDA  0,445(7) 	set return address to halt
  4:    JEQ  5,330(7) 	jump to main
449:   HALT  0,0,0 	
