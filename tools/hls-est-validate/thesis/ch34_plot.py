"""Figure style of the chapter 3 / 4 generators (matplotlib, static PDF + PNG for the thesis).

Colours are the first categorical slots of the dataviz reference palette (light mode), in fixed order;
text stays in ink colours, grids are recessive, one y-axis per chart.
"""
import matplotlib

matplotlib.use("Agg")
import matplotlib.pyplot as plt  # noqa: E402

SERIES = ["#2a78d6", "#eb6834", "#1baf7a", "#eda100", "#e87ba4", "#008300", "#6250d6", "#e34948"]
INK = "#0b0b0b"
INK2 = "#52514e"
GRID = "#e4e3df"


def style(ax):
    ax.spines["top"].set_visible(False)
    ax.spines["right"].set_visible(False)
    for s in ("left", "bottom"):
        ax.spines[s].set_color(INK2)
        ax.spines[s].set_linewidth(0.8)
    ax.tick_params(colors=INK2, labelsize=8)
    ax.xaxis.label.set_color(INK)
    ax.yaxis.label.set_color(INK)
    ax.set_axisbelow(True)


def save(fig, path_stem, gen_line):
    """Save <stem>.pdf and <stem>.png; the generator line goes into the PDF metadata."""
    fig.savefig(f"{path_stem}.pdf", metadata={"Subject": gen_line})
    fig.savefig(f"{path_stem}.png", dpi=200)
    plt.close(fig)
