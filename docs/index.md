---
layout: default
title: index
---

# 競技プログラミング　ライブラリノート

## {{ page.title }}
<ul>
    {% for p in site.pages %}
    {% if p.title != page.title %}
    <li><a href="{{ p.url | relative_url }}">{{ p.title }}</a></li>
    {% endif %}
    {% endfor %}
</ul>