<?php
/**
 * @file
 * Show pages allowing reordering of nodes within a taxonomy
 */

/**
 * Generate a form allowing reordering of nodes within the given term.
 */
function reorder_term_order_form($form, &$form_state, $term) {
  $nodes = reorder_select_nodes($term->tid);

  foreach ($nodes as $nid => $node) {
    $form[$nid]['title'] = array(
      '#markup' => $node->title);

    $form[$nid]['weight'] = array(
      '#type' => 'weight',
      '#title' => t('Weight'),
      '#default_value' => $node->weight);
  }

  $form['#nids'] = array_keys($nodes);
  $form['#term'] = $term;
  $form['#tree'] = TRUE;

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Order'));

  drupal_set_title(reorder_term_order_title($term));

  return $form;
}

/**
 * Save the configured node weights
 */
function reorder_term_order_form_submit($form, &$form_state) {
  foreach ($form['#nids'] as $nid) {
    $weight = $form_state['values'][$nid]['weight'];
    $tid = $form['#term']->tid;
    reorder_save($tid, $nid, $weight);
  }
}

/**
 * Render the node reordering form
 */
function theme_reorder_term_order_form($form) {
  $form = $form['form'];
  $headers = array('', 'Node', 'Weight');
  $weight_class = 'term-reorder-weight';
  $rows = array();

  foreach ($form['#nids'] as $nid) {
    $row = array(array('class' => 'slide-cross'));
    $row[] = drupal_render($form[$nid]['title']);
    $form[$nid]['weight']['#attributes']['class'] = array($weight_class);
    $row[] = drupal_render($form[$nid]['weight']);

    $rows[] = array('data' => $row, 'class' => array('draggable'));
  }

  $output = theme('table', array(
                                'headers' => $headers,
                                'rows' => $rows,
                                'attributes' => array('id' => 'term-reorder')));
  $output .= drupal_render_children($form);

  drupal_add_tabledrag('term-reorder', 'order', 'sibling', $weight_class);

  $output .= theme('pager');

  return $output;
}
