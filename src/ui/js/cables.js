// AI GENERATED (AND HUMAN ADAPTED) CABLE DRAWING LOGIC

const GRAVITY = 0.5;       // force vers le bas appliquée à chaque point
const DAMPING = 0.985;     // amortissement de la vitesse (évite l'emballement)
const SEGMENTS = 20;       // nombre de segments du câble // 20
const ITERATIONS = 14;     // nombre de passes de résolution des contraintes par frame
// const SLACK = 1.18;        // mou du câble (1 = tendu, >1 = plus de pendage)
const SLACK = 1.25;        // mou du câble (1 = tendu, >1 = plus de pendage)

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
  constructor(x1, y1, x2, y2, source, target, sourceContainer, targetContainer, color, id){
    this.source = source;
    this.target = target;
    this.color = color;
    this.sourceContainer = sourceContainer;
    this.targetContainer = targetContainer;
    this.id = id;
    this.points = [];
    const dx = (x2 - x1) / SEGMENTS, dy = (y2 - y1) / SEGMENTS;
    for (let i = 0; i <= SEGMENTS; i++) {
      this.points.push(new Point(x1 + dx * i, y1 + dy * i, i === 0 || i === SEGMENTS));
    }
  }

  pinEnd(which, x, y){
    const p = which === 0 ? this.points[0] : this.points[this.points.length - 1];
    p.x = x; p.y = y; p.ox = x; p.oy = y;
  }

  update(){
    const a = this.points[0], b = this.points[this.points.length - 1];
    const dist = Math.hypot(b.x - a.x, b.y - a.y);
    this.restLen = dist / SEGMENTS * SLACK;
    this.points.forEach(p => p.step());
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
    this.pathThrough(ctx, 5);
    ctx.strokeStyle = 'rgba(0,0,0,0.25)';
    ctx.lineWidth = 7; ctx.lineCap = 'round'; ctx.lineJoin = 'round';
    ctx.stroke();

    // corps du câble
    this.pathThrough(ctx, 0);
    ctx.strokeStyle = this.color;
    ctx.lineWidth = 8; ctx.lineCap = 'round'; ctx.lineJoin = 'round';
    ctx.stroke();

    // reflet (sheen)
    this.pathThrough(ctx, -1.4);
    ctx.strokeStyle = 'rgba(255,255,255,0.32)';
    ctx.lineWidth = 1.6; ctx.lineCap = 'round';
    ctx.stroke();
  }
}

function createNewCable(cables, source, target, sourceContainer, targetContainer, color) {
  const sourcePos = source.mapToItem(null, source.width / 2, source.height / 2);
  const targetPos = target.mapToItem(null, target.width / 2, target.height / 2);
  const cable = new Cable(
      sourcePos.x,
      sourcePos.y,
      targetPos.x,
      targetPos.y,
      source,
      target,
      sourceContainer,
      targetContainer,
      color,
      cables.length
  );
  return cable;
}

function findCable(cables, id) {
  return cables.find((c) => c.id === id)
}

function removeCable(cables, id) {
  const cableIdx = cables.findIndex((c) => c.id === id);
  cables.splice(cableIdx, 1);
}

