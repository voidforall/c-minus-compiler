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
* --> Function (search)
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
 13:    LDC  0,-8(0) 	ExprId: load id offset to ac
 14:    ADD  0,4,0 	ExprId: fp + offset = base address
 15:    LDA  0,0(0) 	ExprId: load id address
* <-- ExprId
 16:     ST  0,-11(4) 	assign: push id(addr) to fp
* --> Const
 17:    LDC  0,1(0) 	Const: load val to ac
* <-- Const
 18:     LD  1,-11(4) 	assign: load id(addr) to ac1
 19:     ST  0,0(1) 	assign: assign expr(ac)->id(ac1)
* <-- Assign
* --> Assign
* --> ExprId
 20:    LDC  0,-5(0) 	ExprId: load id offset to ac
 21:    ADD  0,4,0 	ExprId: fp + offset = base address
 22:    LDA  0,0(0) 	ExprId: load id address
* <-- ExprId
 23:     ST  0,-11(4) 	assign: push id(addr) to fp
* --> Const
 24:    LDC  0,0(0) 	Const: load val to ac
* <-- Const
 25:     LD  1,-11(4) 	assign: load id(addr) to ac1
 26:     ST  0,0(1) 	assign: assign expr(ac)->id(ac1)
* <-- Assign
* --> Assign
* --> ExprId
 27:    LDC  0,-6(0) 	ExprId: load id offset to ac
 28:    ADD  0,4,0 	ExprId: fp + offset = base address
 29:    LDA  0,0(0) 	ExprId: load id address
* <-- ExprId
 30:     ST  0,-11(4) 	assign: push id(addr) to fp
* --> Op
* --> ExprId
 31:    LDC  0,-3(0) 	ExprId: load id offset to ac
 32:    ADD  0,4,0 	ExprId: fp + offset = base address
 33:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
 34:     ST  0,-12(4) 	op: push operand1 to mp
* --> Const
 35:    LDC  0,1(0) 	Const: load val to ac
* <-- Const
 36:     LD  1,-12(4) 	op: load operand1 from mp
 37:    SUB  0,1,0 	op: Minus
* <-- Op
 38:     LD  1,-11(4) 	assign: load id(addr) to ac1
 39:     ST  0,0(1) 	assign: assign expr(ac)->id(ac1)
* <-- Assign
* --> Assign
* --> ExprId
 40:    LDC  0,-7(0) 	ExprId: load id offset to ac
 41:    ADD  0,4,0 	ExprId: fp + offset = base address
 42:    LDA  0,0(0) 	ExprId: load id address
* <-- ExprId
 43:     ST  0,-11(4) 	assign: push id(addr) to fp
* --> Op
* --> Op
* --> ExprId
 44:    LDC  0,-5(0) 	ExprId: load id offset to ac
 45:    ADD  0,4,0 	ExprId: fp + offset = base address
 46:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
 47:     ST  0,-12(4) 	op: push operand1 to mp
* --> ExprId
 48:    LDC  0,-6(0) 	ExprId: load id offset to ac
 49:    ADD  0,4,0 	ExprId: fp + offset = base address
 50:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
 51:     LD  1,-12(4) 	op: load operand1 from mp
 52:    ADD  0,1,0 	op: Plus
* <-- Op
 53:     ST  0,-12(4) 	op: push operand1 to mp
* --> Const
 54:    LDC  0,2(0) 	Const: load val to ac
* <-- Const
 55:     LD  1,-12(4) 	op: load operand1 from mp
 56:    DIV  0,1,0 	op: Divide
* <-- Op
 57:     LD  1,-11(4) 	assign: load id(addr) to ac1
 58:     ST  0,0(1) 	assign: assign expr(ac)->id(ac1)
* <-- Assign
* --> Assign
* --> ExprId
 59:    LDC  0,-9(0) 	ExprId: load id offset to ac
 60:    ADD  0,4,0 	ExprId: fp + offset = base address
 61:    LDA  0,0(0) 	ExprId: load id address
* <-- ExprId
 62:     ST  0,-11(4) 	assign: push id(addr) to fp
* --> Const
 63:    LDC  0,1000(0) 	Const: load val to ac
* <-- Const
 64:     LD  1,-11(4) 	assign: load id(addr) to ac1
 65:     ST  0,0(1) 	assign: assign expr(ac)->id(ac1)
* <-- Assign
* --> While
* --> Op
* --> Op
* --> Op
* --> ExprId
 66:    LDC  0,-8(0) 	ExprId: load id offset to ac
 67:    ADD  0,4,0 	ExprId: fp + offset = base address
 68:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
 69:     ST  0,-11(4) 	op: push operand1 to mp
* --> Const
 70:    LDC  0,1(0) 	Const: load val to ac
* <-- Const
 71:     LD  1,-11(4) 	op: load operand1 from mp
 72:    SUB  0,1,0 	op: ==
 73:    JEQ  0,2(7) 	if ==, pc = pc + 2
 74:    LDC  0,0(0) 	if false, ac = 0
 75:    LDA  7,1(7) 	if false, skip next
 76:    LDC  0,1(0) 	if true, ac = 1
* <-- Op
 77:     ST  0,-11(4) 	op: push operand1 to mp
* --> Op
* --> ExprId
 78:    LDC  0,-5(0) 	ExprId: load id offset to ac
 79:    ADD  0,4,0 	ExprId: fp + offset = base address
 80:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
 81:     ST  0,-12(4) 	op: push operand1 to mp
* --> ExprId
 82:    LDC  0,-6(0) 	ExprId: load id offset to ac
 83:    ADD  0,4,0 	ExprId: fp + offset = base address
 84:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
 85:     LD  1,-12(4) 	op: load operand1 from mp
 86:    SUB  0,1,0 	op: <
 87:    JLT  0,2(7) 	if <, pc = pc + 2
 88:    LDC  0,0(0) 	if false, ac = 0
 89:    LDA  7,1(7) 	if false, skip next
 90:    LDC  0,1(0) 	if true, ac = 1
* <-- Op
 91:     LD  1,-11(4) 	op: load operand1 from mp
 92:    MUL  0,1,0 	op: Times
* <-- Op
 93:     ST  0,-11(4) 	op: push operand1 to mp
* --> Const
 94:    LDC  0,1(0) 	Const: load val to ac
* <-- Const
 95:     LD  1,-11(4) 	op: load operand1 from mp
 96:    SUB  0,1,0 	op: ==
 97:    JEQ  0,2(7) 	if ==, pc = pc + 2
 98:    LDC  0,0(0) 	if false, ac = 0
 99:    LDA  7,1(7) 	if false, skip next
100:    LDC  0,1(0) 	if true, ac = 1
* <-- Op
* --> If
* --> Op
* --> ExprId
102:    LDC  0,-2(0) 	ExprId: load id offset to ac
103:    ADD  0,4,0 	ExprId: fp + offset = base address
104:     LD  0,0(0) 	load absolute address
105:     ST  0,-11(4) 	ExprId: push base address to mp
* --> ExprId
106:    LDC  0,-7(0) 	ExprId: load id offset to ac
107:    ADD  0,4,0 	ExprId: fp + offset = base address
108:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
109:     LD  1,-11(4) 	ExprId: load base address to ac1
110:    SUB  0,1,0 	ExprId: base address - index = index address
111:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
112:     ST  0,-11(4) 	op: push operand1 to mp
* --> ExprId
113:    LDC  0,-4(0) 	ExprId: load id offset to ac
114:    ADD  0,4,0 	ExprId: fp + offset = base address
115:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
116:     LD  1,-11(4) 	op: load operand1 from mp
117:    SUB  0,1,0 	op: ==
118:    JEQ  0,2(7) 	if ==, pc = pc + 2
119:    LDC  0,0(0) 	if false, ac = 0
120:    LDA  7,1(7) 	if false, skip next
121:    LDC  0,1(0) 	if true, ac = 1
* <-- Op
* --> Assign
* --> ExprId
123:    LDC  0,-8(0) 	ExprId: load id offset to ac
124:    ADD  0,4,0 	ExprId: fp + offset = base address
125:    LDA  0,0(0) 	ExprId: load id address
* <-- ExprId
126:     ST  0,-11(4) 	assign: push id(addr) to fp
* --> Const
127:    LDC  0,0(0) 	Const: load val to ac
* <-- Const
128:     LD  1,-11(4) 	assign: load id(addr) to ac1
129:     ST  0,0(1) 	assign: assign expr(ac)->id(ac1)
* <-- Assign
* --> Assign
* --> ExprId
130:    LDC  0,-9(0) 	ExprId: load id offset to ac
131:    ADD  0,4,0 	ExprId: fp + offset = base address
132:    LDA  0,0(0) 	ExprId: load id address
* <-- ExprId
133:     ST  0,-11(4) 	assign: push id(addr) to fp
* --> ExprId
134:    LDC  0,-7(0) 	ExprId: load id offset to ac
135:    ADD  0,4,0 	ExprId: fp + offset = base address
136:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
137:     LD  1,-11(4) 	assign: load id(addr) to ac1
138:     ST  0,0(1) 	assign: assign expr(ac)->id(ac1)
* <-- Assign
* --> If
* --> Op
* --> ExprId
140:    LDC  0,-2(0) 	ExprId: load id offset to ac
141:    ADD  0,4,0 	ExprId: fp + offset = base address
142:     LD  0,0(0) 	load absolute address
143:     ST  0,-11(4) 	ExprId: push base address to mp
* --> ExprId
144:    LDC  0,-7(0) 	ExprId: load id offset to ac
145:    ADD  0,4,0 	ExprId: fp + offset = base address
146:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
147:     LD  1,-11(4) 	ExprId: load base address to ac1
148:    SUB  0,1,0 	ExprId: base address - index = index address
149:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
150:     ST  0,-11(4) 	op: push operand1 to mp
* --> ExprId
151:    LDC  0,-4(0) 	ExprId: load id offset to ac
152:    ADD  0,4,0 	ExprId: fp + offset = base address
153:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
154:     LD  1,-11(4) 	op: load operand1 from mp
155:    SUB  0,1,0 	op: >
156:    JGT  0,2(7) 	if >, pc = pc + 2
157:    LDC  0,0(0) 	if false, ac = 0
158:    LDA  7,1(7) 	if false, skip next
159:    LDC  0,1(0) 	if true, ac = 1
* <-- Op
* --> Assign
* --> ExprId
161:    LDC  0,-6(0) 	ExprId: load id offset to ac
162:    ADD  0,4,0 	ExprId: fp + offset = base address
163:    LDA  0,0(0) 	ExprId: load id address
* <-- ExprId
164:     ST  0,-11(4) 	assign: push id(addr) to fp
* --> ExprId
165:    LDC  0,-7(0) 	ExprId: load id offset to ac
166:    ADD  0,4,0 	ExprId: fp + offset = base address
167:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
168:     LD  1,-11(4) 	assign: load id(addr) to ac1
169:     ST  0,0(1) 	assign: assign expr(ac)->id(ac1)
* <-- Assign
* --> Assign
* --> ExprId
170:    LDC  0,-7(0) 	ExprId: load id offset to ac
171:    ADD  0,4,0 	ExprId: fp + offset = base address
172:    LDA  0,0(0) 	ExprId: load id address
* <-- ExprId
173:     ST  0,-11(4) 	assign: push id(addr) to fp
* --> Op
* --> Op
* --> ExprId
174:    LDC  0,-5(0) 	ExprId: load id offset to ac
175:    ADD  0,4,0 	ExprId: fp + offset = base address
176:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
177:     ST  0,-12(4) 	op: push operand1 to mp
* --> ExprId
178:    LDC  0,-6(0) 	ExprId: load id offset to ac
179:    ADD  0,4,0 	ExprId: fp + offset = base address
180:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
181:     LD  1,-12(4) 	op: load operand1 from mp
182:    ADD  0,1,0 	op: Plus
* <-- Op
183:     ST  0,-12(4) 	op: push operand1 to mp
* --> Const
184:    LDC  0,2(0) 	Const: load val to ac
* <-- Const
185:     LD  1,-12(4) 	op: load operand1 from mp
186:    DIV  0,1,0 	op: Divide
* <-- Op
187:     LD  1,-11(4) 	assign: load id(addr) to ac1
188:     ST  0,0(1) 	assign: assign expr(ac)->id(ac1)
* <-- Assign
* --> Assign
* --> ExprId
190:    LDC  0,-5(0) 	ExprId: load id offset to ac
191:    ADD  0,4,0 	ExprId: fp + offset = base address
192:    LDA  0,0(0) 	ExprId: load id address
* <-- ExprId
193:     ST  0,-11(4) 	assign: push id(addr) to fp
* --> Op
* --> ExprId
194:    LDC  0,-7(0) 	ExprId: load id offset to ac
195:    ADD  0,4,0 	ExprId: fp + offset = base address
196:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
197:     ST  0,-12(4) 	op: push operand1 to mp
* --> Const
198:    LDC  0,1(0) 	Const: load val to ac
* <-- Const
199:     LD  1,-12(4) 	op: load operand1 from mp
200:    ADD  0,1,0 	op: Plus
* <-- Op
201:     LD  1,-11(4) 	assign: load id(addr) to ac1
202:     ST  0,0(1) 	assign: assign expr(ac)->id(ac1)
* <-- Assign
* --> Assign
* --> ExprId
203:    LDC  0,-7(0) 	ExprId: load id offset to ac
204:    ADD  0,4,0 	ExprId: fp + offset = base address
205:    LDA  0,0(0) 	ExprId: load id address
* <-- ExprId
206:     ST  0,-11(4) 	assign: push id(addr) to fp
* --> Op
* --> Op
* --> ExprId
207:    LDC  0,-5(0) 	ExprId: load id offset to ac
208:    ADD  0,4,0 	ExprId: fp + offset = base address
209:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
210:     ST  0,-12(4) 	op: push operand1 to mp
* --> ExprId
211:    LDC  0,-6(0) 	ExprId: load id offset to ac
212:    ADD  0,4,0 	ExprId: fp + offset = base address
213:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
214:     LD  1,-12(4) 	op: load operand1 from mp
215:    ADD  0,1,0 	op: Plus
* <-- Op
216:     ST  0,-12(4) 	op: push operand1 to mp
* --> Const
217:    LDC  0,2(0) 	Const: load val to ac
* <-- Const
218:     LD  1,-12(4) 	op: load operand1 from mp
219:    DIV  0,1,0 	op: Divide
* <-- Op
220:     LD  1,-11(4) 	assign: load id(addr) to ac1
221:     ST  0,0(1) 	assign: assign expr(ac)->id(ac1)
* <-- Assign
160:    JEQ  0,29(7) 	If false, jump to else part
189:    LDA  7,32(7) 	Jump to the end
* <-- If
122:    JEQ  0,17(7) 	If false, jump to else part
139:    LDA  7,82(7) 	Jump to the end
* <-- If
222:    LDA  7,-157(7) 	Jump to while condition
101:    JEQ  0,121(7) 	If false, end loop
* <-- While
* --> Return
* --> ExprId
223:    LDC  0,-9(0) 	ExprId: load id offset to ac
224:    ADD  0,4,0 	ExprId: fp + offset = base address
225:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
* <-- Return
* <- End function body
226:     LD  7,-1(4) 	return to caller
* <-- Function (search)
* --> Function (main)
227:     ST  0,-1(4) 	save return address in fp + retFO
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
228:    LDC  0,-1004(0) 	ExprId: load id offset to ac
229:    ADD  0,4,0 	ExprId: fp + offset = base address
230:    LDA  0,0(0) 	ExprId: load id address
* <-- ExprId
231:     ST  0,-1007(4) 	assign: push id(addr) to fp
* --> Calling (input)
232:     ST  4,-1008(4) 	store old frame pointer
233:    LDA  4,-1008(4) 	push new frame
234:    LDA  0,1(7) 	save return address in ac
235:    LDA  7,-231(7) 	jump to the function
236:     LD  4,0(4) 	restore frame pointer
* <-- Calling (input)
237:     LD  1,-1007(4) 	assign: load id(addr) to ac1
238:     ST  0,0(1) 	assign: assign expr(ac)->id(ac1)
* <-- Assign
* --> Assign
* --> ExprId
239:    LDC  0,-1002(0) 	ExprId: load id offset to ac
240:    ADD  0,4,0 	ExprId: fp + offset = base address
241:    LDA  0,0(0) 	ExprId: load id address
* <-- ExprId
242:     ST  0,-1007(4) 	assign: push id(addr) to fp
* --> Const
243:    LDC  0,0(0) 	Const: load val to ac
* <-- Const
244:     LD  1,-1007(4) 	assign: load id(addr) to ac1
245:     ST  0,0(1) 	assign: assign expr(ac)->id(ac1)
* <-- Assign
* --> While
* --> Op
* --> ExprId
246:    LDC  0,-1002(0) 	ExprId: load id offset to ac
247:    ADD  0,4,0 	ExprId: fp + offset = base address
248:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
249:     ST  0,-1007(4) 	op: push operand1 to mp
* --> ExprId
250:    LDC  0,-1004(0) 	ExprId: load id offset to ac
251:    ADD  0,4,0 	ExprId: fp + offset = base address
252:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
253:     LD  1,-1007(4) 	op: load operand1 from mp
254:    SUB  0,1,0 	op: <
255:    JLT  0,2(7) 	if <, pc = pc + 2
256:    LDC  0,0(0) 	if false, ac = 0
257:    LDA  7,1(7) 	if false, skip next
258:    LDC  0,1(0) 	if true, ac = 1
* <-- Op
* --> Assign
* --> ExprId
260:    LDC  0,-2(0) 	ExprId: load id offset to ac
261:    ADD  0,4,0 	ExprId: fp + offset = base address
262:     ST  0,-1007(4) 	ExprId: push base address to mp
* --> ExprId
263:    LDC  0,-1002(0) 	ExprId: load id offset to ac
264:    ADD  0,4,0 	ExprId: fp + offset = base address
265:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
266:     LD  1,-1007(4) 	ExprId: load base address to ac1
267:    SUB  0,1,0 	ExprId: base address - index = index address
268:    LDA  0,0(0) 	ExprId: load id address
* <-- ExprId
269:     ST  0,-1007(4) 	assign: push id(addr) to fp
* --> Calling (input)
270:     ST  4,-1008(4) 	store old frame pointer
271:    LDA  4,-1008(4) 	push new frame
272:    LDA  0,1(7) 	save return address in ac
273:    LDA  7,-269(7) 	jump to the function
274:     LD  4,0(4) 	restore frame pointer
* <-- Calling (input)
275:     LD  1,-1007(4) 	assign: load id(addr) to ac1
276:     ST  0,0(1) 	assign: assign expr(ac)->id(ac1)
* <-- Assign
* --> Assign
* --> ExprId
277:    LDC  0,-1002(0) 	ExprId: load id offset to ac
278:    ADD  0,4,0 	ExprId: fp + offset = base address
279:    LDA  0,0(0) 	ExprId: load id address
* <-- ExprId
280:     ST  0,-1007(4) 	assign: push id(addr) to fp
* --> Op
* --> ExprId
281:    LDC  0,-1002(0) 	ExprId: load id offset to ac
282:    ADD  0,4,0 	ExprId: fp + offset = base address
283:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
284:     ST  0,-1008(4) 	op: push operand1 to mp
* --> Const
285:    LDC  0,1(0) 	Const: load val to ac
* <-- Const
286:     LD  1,-1008(4) 	op: load operand1 from mp
287:    ADD  0,1,0 	op: Plus
* <-- Op
288:     LD  1,-1007(4) 	assign: load id(addr) to ac1
289:     ST  0,0(1) 	assign: assign expr(ac)->id(ac1)
* <-- Assign
290:    LDA  7,-45(7) 	Jump to while condition
259:    JEQ  0,31(7) 	If false, end loop
* <-- While
* --> Assign
* --> ExprId
291:    LDC  0,-1005(0) 	ExprId: load id offset to ac
292:    ADD  0,4,0 	ExprId: fp + offset = base address
293:    LDA  0,0(0) 	ExprId: load id address
* <-- ExprId
294:     ST  0,-1007(4) 	assign: push id(addr) to fp
* --> Calling (input)
295:     ST  4,-1008(4) 	store old frame pointer
296:    LDA  4,-1008(4) 	push new frame
297:    LDA  0,1(7) 	save return address in ac
298:    LDA  7,-294(7) 	jump to the function
299:     LD  4,0(4) 	restore frame pointer
* <-- Calling (input)
300:     LD  1,-1007(4) 	assign: load id(addr) to ac1
301:     ST  0,0(1) 	assign: assign expr(ac)->id(ac1)
* <-- Assign
* --> Assign
* --> ExprId
302:    LDC  0,-1003(0) 	ExprId: load id offset to ac
303:    ADD  0,4,0 	ExprId: fp + offset = base address
304:    LDA  0,0(0) 	ExprId: load id address
* <-- ExprId
305:     ST  0,-1007(4) 	assign: push id(addr) to fp
* --> Calling (search)
* --> ExprId
306:    LDC  0,-2(0) 	ExprId: load id offset to ac
307:    ADD  0,4,0 	ExprId: fp + offset = base address
308:    LDA  0,0(0) 	ExprId: load id address
* <-- ExprId
309:     ST  0,-1010(4) 	store parameter 0
* --> ExprId
310:    LDC  0,-1004(0) 	ExprId: load id offset to ac
311:    ADD  0,4,0 	ExprId: fp + offset = base address
312:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
313:     ST  0,-1011(4) 	store parameter 1
* --> ExprId
314:    LDC  0,-1005(0) 	ExprId: load id offset to ac
315:    ADD  0,4,0 	ExprId: fp + offset = base address
316:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
317:     ST  0,-1012(4) 	store parameter 2
318:     ST  4,-1008(4) 	store old frame pointer
319:    LDA  4,-1008(4) 	push new frame
320:    LDA  0,1(7) 	save return address in ac
321:    LDA  7,-310(7) 	jump to the function
322:     LD  4,0(4) 	restore frame pointer
* <-- Calling (search)
323:     LD  1,-1007(4) 	assign: load id(addr) to ac1
324:     ST  0,0(1) 	assign: assign expr(ac)->id(ac1)
* <-- Assign
* --> Calling (output)
* --> ExprId
325:    LDC  0,-1003(0) 	ExprId: load id offset to ac
326:    ADD  0,4,0 	ExprId: fp + offset = base address
327:     LD  0,0(0) 	ExprId: load id value
* <-- ExprId
328:     ST  0,-1009(4) 	store parameter 0
329:     ST  4,-1007(4) 	store old frame pointer
330:    LDA  4,-1007(4) 	push new frame
331:    LDA  0,1(7) 	save return address in ac
332:    LDA  7,-325(7) 	jump to the function
333:     LD  4,0(4) 	restore frame pointer
* <-- Calling (output)
* --> Return
* --> Const
334:    LDC  0,0(0) 	Const: load val to ac
* <-- Const
* <-- Return
* <- End function body
335:     LD  7,-1(4) 	return to caller
* <-- Function (main)
* End of execution
  2:    LDA  4,-2(6) 	load initial frame pointer
  3:    LDA  0,332(7) 	set return address to halt
  4:    JEQ  5,222(7) 	jump to main
336:   HALT  0,0,0 	
