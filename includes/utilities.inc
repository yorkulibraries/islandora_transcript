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
  $transcript_url = url("islandora/object/{$object->id}/datastream/TRANSCRIPT/view", array('absolute' => TRUE));
  $transcript = file_get_contents($transcript_url);
  return array(
    'transcript' => array(
      '#markup' => $transcript,
    ),
  );
}
