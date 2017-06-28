<?php

/**
 * @file
 * This file contains the functions to render the transcript tab.
 */

/**
 * Renders the TRANSCRIPT tab.
 *
 * @pararm AbstractObject $object
 *   The object the TRANSCRIPT belongs to.
 *
 * @return array
 *   A renderable array representing the tab.
 */
function islandora_transcript_view(AbstractObject $object) {
  if ($object['TRANSCRIPT']->mimetype == 'application/pdf') {
    module_load_include('inc', 'islandora', 'includes/solution_packs');
    $viewer = islandora_get_viewer(array('dsid' => 'TRANSCRIPT'), 'islandora_pdf_viewers', $object);
    return array(
      'transcript' => array(
        '#markup' => sprintf('<pre>%s</pre>', $viewer ? $viewer : ''),
      ),
    );
  }
  else {
    $transcript = $object['TRANSCRIPT']->content;
    return array(
      'transcript' => array(
        '#markup' => '<pre>' . wordwrap($transcript) . '</pre>',
      ),
    );
  }
}

/**
 * Updates this object's TRANSCRIPT datastream.
 *
 * @param array $form
 *   The Drupal form definition.
 * @param array $form_state
 *   The Drupal form state.
 * @param AbstractObject $object
 *   The page object to be updated.
 *
 * @return array
 *   The Drupal form definition.
 */
function islandora_transcript_edit_transcript_form(array $form, array &$form_state, AbstractObject $object) {
  $pid = $object->id;
  $path = drupal_get_path('module', 'islandora_transcript');
  $form_state['object'] = $object;
  $form = array();
  $label = $object->label;
  $form['transcript'] = array(
    '#title' => t('Current Transcript'),
    '#type' => 'textarea',
    '#default_value' => $object['TRANSCRIPT']->content,
    '#rows' => 40,
    '#cols' => 20,
    '#attributes' => array('class' => array('transcript_window')),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Update Transcript'),
  );
  $form['pid'] = array(
    '#type' => 'hidden',
    '#value' => $object->id,
  );
  return $form;
}

/**
 * Submit handler for the edit form.
 *
 * @param array $form
 *   The Drupal form definition.
 * @param array $form_state
 *   The Drupal form state.
 */
function islandora_transcript_edit_transcript_form_submit(array $form, array &$form_state) {
  module_load_include('inc', 'islandora_transcript', 'includes/utilities');
  $object = islandora_object_load($form_state['values']['pid']);
  $success = TRUE;
  try {
    $object["TRANSCRIPT"]->content = $form_state['values']['transcript'];
  }
  catch (Exception $e) {
    $success = FALSE;
    drupal_set_message(t("TRANSCRIPT update failed."));
  }
  if ($success) {
    drupal_set_message(t("TRANSCRIPT successfully updated."));
  }
}
