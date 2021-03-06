--TEST--
CommonMark\CQL children, children, children with constraint
--FILE--
<?php
$doc = \CommonMark\Parse(<<<EOD
  * item 1 list 1
  * item 2 list 1
  * > block quote
EOD
);

$call = new \CommonMark\CQL("/children[
  /children[
    /children(Paragraph)
  ]
]");

$call($doc, function(\CommonMark\Node $root, \CommonMark\Node $node) {
	if ($node instanceof \CommonMark\Node\Paragraph) {
		echo "OK\n";
	} else  echo "FAIL\n";
});
?>
--EXPECT--
OK
OK

