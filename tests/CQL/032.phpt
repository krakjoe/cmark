--TEST--
CommonMark\CQL negation
--FILE--
<?php
$doc = \CommonMark\Parse(<<<EOD
  paragraph
  * item 1
EOD
);

$call = new \CommonMark\CQL(<<<EOD
/firstChild(~Paragraph)
EOD
);

$call($doc, function(\CommonMark\Node $root, \CommonMark\Node $node) {
	if ($node instanceof \CommonMark\Node\BulletList) {
		echo "OK";
	} else  echo "FAIL";
});
?>
--EXPECT--
OK

