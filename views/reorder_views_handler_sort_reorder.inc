<?php
/**
 * @file
 * The views handler allowing sorting by order within taxonomy
 */

/**
 * Sort handler that sorts based upon the weight of a node within a term
 */
class reorder_views_handler_sort_weight extends views_handler_sort {

    function query() {
        $this->ensure_my_table();

        // find if there is a filter on tid
        $tid = FALSE;
        foreach ($this->query->where as $group) {
            foreach ($group['conditions'] as $condition) {
                if ($condition['field'] == 'taxonomy_index.tid' && $condition['operator'] == '=') {
                    $tid = $condition['value'];
                }
            }
        }

        // if there was not a term filter found, we will show nothing
        $this->query->add_where(50, 'reorder.tid', $tid);
        $this->query->add_orderby($this->table_alias,
                                  $this->real_field,
                                  $this->options['order']);
    }
}
