<?php
/**
 * @file
 * Expose the reorder table to views
 */

/**
 * Implements hook_views_data()
 */
function reorder_views_data() {
  $data['reorder']['table'] = array(
    'group' => 'Taxonomy',
    'join' => array(
      'node' => array(
        'left_field' => 'nid',
        'field' => 'nid',
      ),
    ),
  );

  $data['reorder']['weight'] = array(
    'title' => t('Weight in taxonomy'),
    'help' => t('The weight of this node in the given taxonomy'),
    'sort' => array(
      'handler' => 'reorder_views_handler_sort_weight',
    )
  );

  return $data;
}
