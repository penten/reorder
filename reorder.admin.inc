<?php
/**
 * @file
 * Show pages allowing reordering of nodes within a taxonomy
 */

function reorder_term_order_form($form, &$form_state, $term) {
    $nids = taxonomy_select_nodes($term->tid);
    $weighted_nids = array();
    
    foreach ($nids as $nid) {
        $node = node_load($nid);
        $form[$nid]['#node'] = $node;
        $form[$nid]['title'] = array('#markup' => $node->title);
        $form[$nid]['weight'] = array('#type' => 'weight', '#title' => t('Weight'), '#default_value' => reorder_weight($term->tid, $nid));
        $weighted_nids[$nid] = $form[$nid]['weight']['#default_value'];
    }
    asort($weighted_nids);
    
    $form['#nids'] = array_keys($weighted_nids);
    $form['#term'] = $term;
    $form['#tree'] = TRUE;
    $form['submit'] = array('#type' => 'submit', '#value' => t('Save Order'));

    drupal_set_title(reorder_term_order_title($term));

    return $form;
}

function reorder_term_order_form_submit($form, &$form_state) {
    foreach ($form['#nids'] as $nid) {
        $weight = $form_state['values'][$nid]['weight'];
        $tid = $form['#term']->tid;
        reorder_save($tid, $nid, $weight);
    }
}

function theme_reorder_term_order_form($form) {
    $form = $form['form'];
    $headers = array('', 'Node', 'Weight');
    $rows = array();
    
    foreach ($form['#nids'] as $nid) {
        $row = array(array('class' => 'slide-cross'));
        $row[] = drupal_render($form[$nid]['title']);
        $form[$nid]['weight']['#attributes']['class'] = array('term-reorder-weight');
        $row[] = drupal_render($form[$nid]['weight']);

        $rows[] = array('data' => $row, 'class' => array('draggable'));
    }

    $output = theme('table', array('headers' => $headers, 'rows' => $rows, 'attributes' => array('id' => 'term-reorder')));
    $output .= drupal_render_children($form);

    drupal_add_tabledrag('term-reorder', 'order', 'sibling', 'term-reorder-weight');

    return $output;
}