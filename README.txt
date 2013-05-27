Allows reordering of nodes within a taxonomy term.

This module does not modify the taxonomy listing pages, it simply adds a weight
to nodes that can be used when ordering views.

There are two primary differences between Reorder and the nodeorder module:

- Reorder does not modify the behaviour of taxonomy in any way, it simply
exposes a field to views that allows reordering nodes by their weight in a
given taxonomy. In other words the configured node order will not be respected
on taxonomy pages.
- Reorder adds a new table to hold node weights instead of the more fragile
solution of adding a column to a taxonomy table, avoiding issues where taxonomy
writes over configured node weights.
