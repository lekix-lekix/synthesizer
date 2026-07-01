// AI GENERATED (AND HUMAN ADAPTED) CABLE DRAWING LOGIC

const GRAVITY = 0.5;       // force vers le bas appliquée à chaque point
const DAMPING = 0.985;     // amortissement de la vitesse (évite l'emballement)
const SEGMENTS = 20;       // nombre de segments du câble
const ITERATIONS = 14;     // nombre de passes de résolution des contraintes par frame
const SLACK = 1.18;        // mou du câble (1 = tendu, >1 = plus de pendage)

class Point {
  constructor(x, y, pinned){
    this.x = x; this.y = y;
    this.ox = x; this.oy = y;
    this.pinned = !!pinned;
  }
  step(){
    if (this.pinned) return;
    const vx = (this.x - this.ox) * DAMPING;
    const vy = (this.y - this.oy) * DAMPING;
    this.ox = this.x; this.oy = this.y;
    this.x += vx;
    this.y += vy + GRAVITY;
  }
}

class Cable {
  constructor(x1, y1, x2, y2, color){
    this.color = color;
    this.points = [];
    const dx = (x2 - x1) / SEGMENTS, dy = (y2 - y1) / SEGMENTS;
    for (let i = 0; i <= SEGMENTS; i++) {
      this.points.push(new Point(x1 + dx * i, y1 + dy * i, i === 0 || i === SEGMENTS));
    }
    this.restLen = Math.hypot(x2 - x1, y2 - y1) / SEGMENTS * SLACK;
  }

  // Fixe une extrémité du câble à une position donnée (suit le module pendant le drag)
  pinEnd(which, x, y){
    const p = which === 0 ? this.points[0] : this.points[this.points.length - 1];
    p.x = x; p.y = y; p.ox = x; p.oy = y;
  }

  update(){
    this.points.forEach(p => p.step());
    // Résolution itérative des contraintes de distance entre points voisins
    for (let k = 0; k < ITERATIONS; k++) {
      for (let i = 0; i < this.points.length - 1; i++) {
        const a = this.points[i], b = this.points[i + 1];
        const dx = b.x - a.x, dy = b.y - a.y;
        const dist = Math.hypot(dx, dy) || 0.0001;
        const diff = (dist - this.restLen) / dist;
        const ox = dx * 0.5 * diff, oy = dy * 0.5 * diff;
        if (!a.pinned) { a.x += ox; a.y += oy; }
        if (!b.pinned) { b.x -= ox; b.y -= oy; }
      }
    }
  }

  pathThrough(ctx, yOffset){
    const pts = this.points;
    ctx.beginPath();
    ctx.moveTo(pts[0].x, pts[0].y + yOffset);
    for (let i = 1; i < pts.length - 1; i++) {
      const xc = (pts[i].x + pts[i + 1].x) / 2;
      const yc = (pts[i].y + pts[i + 1].y) / 2 + yOffset;
      ctx.quadraticCurveTo(pts[i].x, pts[i].y + yOffset, xc, yc);
    }
    ctx.lineTo(pts[pts.length - 1].x, pts[pts.length - 1].y + yOffset);
  }

  draw(ctx){
    // ombre portée
    // console.log("drawing");
    this.pathThrough(ctx, 5);
    ctx.strokeStyle = 'rgba(0,0,0,0.25)';
    ctx.lineWidth = 7; ctx.lineCap = 'round'; ctx.lineJoin = 'round';
    ctx.stroke();

    // corps du câble
    this.pathThrough(ctx, 0);
    ctx.strokeStyle = this.color;
    ctx.lineWidth = 6; ctx.lineCap = 'round'; ctx.lineJoin = 'round';
    ctx.stroke();

    // reflet (sheen)
    this.pathThrough(ctx, -1.4);
    ctx.strokeStyle = 'rgba(255,255,255,0.32)';
    ctx.lineWidth = 1.6; ctx.lineCap = 'round';
    ctx.stroke();
  }
}

// --- Modules audio (rectangles avec jacks) ---
// const modules = [
//   { x: 50,  y: 120, w: 130, h: 210, label: 'OSC',    sub: 'OUT', jacks: [{ dy: 48 }, { dy: 108 }] },
//   { x: 380, y: 120, w: 130, h: 210, label: 'FILTER', sub: 'IN',  jacks: [{ dy: 48 }, { dy: 108 }] }
// ];

let cables = [];

// function jackPos(m, j, side){
//   return side === 'right' ? { x: m.x + m.w, y: m.y + j.dy } : { x: m.x, y: m.y + j.dy };
// }

// function buildCables(modules){
//   const colors = ['#e8b73f', '#3f7fd6'];
//   if (modules) {
//     cables = modules[0].jacks.map((j, i) => {
//       const p1 = jackPos(modules[0], j, 'right');
//       const p2 = jackPos(modules[1], modules[1].jacks[i], 'left');
//       return new Cable(p1.x, p1.y, p2.x, p2.y, colors[i % colors.length]);
//     });
//     }
// }

function drawModule(m, ctx){
  ctx.fillStyle = '#2b2f3a';
  ctx.beginPath();
  if (ctx.roundRect) ctx.roundRect(m.x, m.y, m.w, m.h, 8);
  else ctx.rect(m.x, m.y, m.w, m.h);
  ctx.fill();

  ctx.fillStyle = '#e7e7ea';
  ctx.font = '500 13px sans-serif';
  ctx.textAlign = 'center';
  ctx.fillText(m.label, m.x + m.w / 2, m.y + 22);

  ctx.fillStyle = '#9a9aa3';
  ctx.font = '400 10px sans-serif';
  ctx.fillText(m.sub, m.x + m.w / 2, m.y + m.h - 12);

  m.jacks.forEach(j => {
    const side = m === modules[0] ? 'right' : 'left';
    const p = jackPos(m, j, side);
    ctx.beginPath(); ctx.arc(p.x, p.y, 7, 0, Math.PI * 2);
    ctx.fillStyle = '#111317'; ctx.fill();
    ctx.beginPath(); ctx.arc(p.x, p.y, 4, 0, Math.PI * 2);
    ctx.fillStyle = '#55565e'; ctx.fill();
  });
}